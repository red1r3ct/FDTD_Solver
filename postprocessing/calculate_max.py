import numpy as np
import matplotlib.pyplot as plt
import argparse
import traceback
import tarfile
import os
import re
import time


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
    regex = re.compile(r"i_(\w+)_(\d+)\.txt")
    try:
        m = regex.search(tar_file.name)
        file_type = m.group(1)
        t = int(m.group(2))
        return t_start <= t <= t_end
    except BaseException:
        return False


def output_spot(name, content, dir_name):
    splited = content.decode("utf-8").split("\n")
    # Get area size
    first_x = float('inf')
    first_y = float('inf')
    last_x = 0
    last_y = 0
    for line in splited:
        line_splited = line.split(" ")
        if len(line_splited) != 3:
            print(line_splited)
            continue
        y = int(line_splited[1])
        x = int(line_splited[0])
        if last_x < x:
            last_x = x
        if first_x > x:
            first_x = x
        if last_y < y:
            last_y = y
        if first_y > y:
            first_y = y
    size_x = last_x - first_x
    size_y = last_y - first_y
    data = np.zeros((size_y + 1, size_x + 1))
    print("File {name} obtain size_x={size_x} size_y={size_y}".format(
        name=name,
        size_x=size_x,
        size_y=size_y
    ))
    # Read to NP array
    for line in splited:
        line_splited = line.split(" ")
        if len(line_splited) != 3:
            print(line_splited)
            continue
        y = int(line_splited[1])
        x = int(line_splited[0])
        val = float(line_splited[2])
        data[y - first_y, x - first_x] = val
    max_val = np.max(data[int(0.25 * size_y):int(0.75 * size_y),
                          int(0.25 * size_x):int(0.75 * size_x)])
    with open(name, 'a') as file:
        file.write(str(max_val) + "\n")
        file.close()


def main(tar_name, t_start, t_end, output_name):
    tar_info, file = read_tarinfo(tar_name)
    dir_name = "max_{}".format(tar_name.replace(".tar.gz", ""))
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
            output_spot("max_" + tf.name, content, dir_name)
        except BaseException:
            traceback.print_exc()
            continue


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--out_name", help="Path to file in which image will be saved")
    parser.add_argument("--tar_file", help="Path to archive")
    parser.add_argument("--t_start", help="Time from to start read files")
    parser.add_argument("--t_end", help="Time until dumps should ba analized")
    args = parser.parse_args()

    out_name = str(args.out_name)
    tar_file = str(args.tar_file)
    t_start = int(args.t_start)
    t_end = int(args.t_end)

    print("Start processing max: tar_file={tar_file}\n out_name={out_name}\n t_start={t_start}\n t_end={t_end}\n".format(
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
