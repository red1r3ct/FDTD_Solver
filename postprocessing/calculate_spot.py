import numpy
import argparse
import traceback
import tarfile
import os


def read_tarinfo(fname):
    tar = tarfile.open(fname)
    return list(tar.getmembers()), tar


def read(file, tar_info):
    f = file.extractfile(tar_info)
    if f is None:
        return None, True
    content = f.read()
    return content, False


def should_parse_file(tar_file, t_start, t_end):
    return True


def output_spot(name, content):
    splited = content.decode("utf-8").split("\n")
    # Get area size
    size_x = 0
    size_y = 0
    for line in splited:
        splited = line.split(" ")
        if len(splited) != 3:
            print(splited)
            continue
        y = int(splited[1])
        x = int(splited[0])
        if size_x < x:
          size_x = x
        if size_y < y:
          size_y = y
    data = np.zeros((size_x, size_y))
    # Read to NP array
    for line in splited:
        splited = line.split(" ")
        if len(splited) != 3:
            print(splited)
            continue
        y = int(splited[1])
        x = int(splited[0])
        val = float(splited[2])
        data[x, y] = val
    # Iterate over each slice
    spot_x = 0
    spot_y = 0
    spot_size = 1000
    for column in data.T:
        print(column)


def main(tar_name, t_start, t_end, output_name):
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
            output_spot("spot_" + tf.name.replace(".txt", ".png"), content)
        except BaseException:
            traceback.print_exc()
            continue

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--out_name", help="Path to file in which image will be saved")
    parser.add_argument("--tar_file", help="Path to archive")
    parser.add_argument("--t_start", help="Time from to start read files")
    parser.add_argument("--t_end", help="Time until dumps should ba analized")
    args = parser.parse_args()

    out_name = str(args.out_name)
    tar_file = str(args.tar_file)
    t_start = int(args.t_start)
    t_end = int(args.t_end)

    print("Start processing spots: tar_file={tar_file}\n out_name={out_name}\n t_start={t_start}\n t_end={t_end}\n".format(
        tar_file=tar_file,
        out_name=out_name,
        t_start=t_start,
        t_end=t_end,
    ))

    main(
        tar_name=tar_file,
        output_name=out_name,
        t_start=t_start,
        t_end=t_end,
    )
