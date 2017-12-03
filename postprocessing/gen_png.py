import tarfile
import traceback
import sys
import os
import scipy.misc
import numpy as np
import argparse


def output_png(filename, lines, step_x, start_x, end_x, start_y, end_y, step_y, caption=""):
    step_x = int(step_x)
    start_x = int(start_x)
    end_x = int(end_x)
    start_y = int(start_y)
    end_y = int(end_y)
    step_y = int(step_y)
    img = np.zeros((int((end_x - start_x) / step_x + 1), int((end_y - start_y) / step_y + 1)), dtype=np.uint8)
    print('''
    Creating Image:
        filename={filename}
        step_x={step_x}
        start_x={start_x}
        end_x={end_x}
        step_y={step_y}
        start_y={start_y}
        end_y={end_y}
    '''.format(
        filename=filename,
        step_x=step_x,
        start_x=start_x,
        end_x=end_x,
        step_y=step_y,
        start_y=start_y,
        end_y=end_y,
    ))
    max = 0
    for line in lines.decode("utf-8").split("\n"):
        splited = line.split(" ")
        if len(splited) != 3:
            print(splited)
            continue
        y = int(splited[1])
        x = int(splited[0])
        if x > end_x or x < start_x or y > end_y or y < start_y:
            continue
        val = float(splited[2])
        if val > max:
            max = val
    if max == 0:
        max = 1

    for line in lines.decode("utf-8").split("\n"):
        try:
            splited = line.split(" ")
            if len(splited) != 3:
                print(splited)
                continue
            y = int(splited[1])
            x = int(splited[0])
            val_raw = float(splited[2])
            if x > end_x or x < start_x or y > end_y or y < start_y:
                continue
            val_bounded = val_raw / max
            img[int((x - start_x) / step_x)][int((y - start_y) / step_y)] = int(val_bounded * 255)
        except BaseException:
            print(BaseException)
            continue
    print(max)
    scipy.misc.imsave(filename, img)


def read_tarinfo(fname):
    tar = tarfile.open(fname)
    return list(tar.getmembers()), tar


def read(file, tar_info):
    f = file.extractfile(tar_info)
    if f is None:
        return None, True
    content = f.read()
    return content, False


def should_parse_file(tf, t_start, t_end):
    return True


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--tar_name", help="Name of a tarfile to open")

    parser.add_argument("--start_x", help="First pixel number in x to show")
    parser.add_argument("--end_x", help="Last pixel number in x to show")
    parser.add_argument("--start_y", help="First pixel number in y to show")
    parser.add_argument("--end_y", help="Last pixel number in y to show")

    parser.add_argument("--t_start", help="Time boundary")
    parser.add_argument("--t_end", help="Time boundary")

    args = parser.parse_args()

    tar_name = str(args.tar_name)
    start_x = int(args.start_x)
    end_x = int(args.end_x)
    start_y = int(args.start_y)
    end_y = int(args.end_y)
    t_start = int(args.t_start)
    t_end = int(args.t_end)

    main_internal(tar_name, start_x, end_x, 1, start_y, end_y, 1, t_start, t_end)


def main_internal(tar_name, start_x, end_x, step_x, start_y, end_y, step_y, t_start, t_end):
    tar_info, file = read_tarinfo(tar_name)
    dir_name = "images_{}".format(tar_name.replace(".tar.gz", ""))
    print(tar_info)

    if not os.path.exists(dir_name):
        os.makedirs(dir_name)
    for tf in tar_info:
        try:
            if not should_parse_file(tf, t_start, t_end):
                print("Skipping: {}".format(tf.name))
                continue
            print("Processing {}".format(tf.name))
            content, isErr = read(file, tf)
            if isErr:
                print("Error during file processing: {}".format(tf.name))
                continue
            output_png("images_" + tf.name.replace(".txt", ".png"), content, step_x, start_x, end_x, start_y, end_y, step_y)
        except BaseException:
            traceback.print_exc()
            continue

if __name__ == '__main__':
    main()

#