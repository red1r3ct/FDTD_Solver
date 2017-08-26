import tarfile
import sys
import os
import scipy.misc
import numpy as np


def output_png(filename, lines, size_x, size_y, step, start_x, end_x, start_y, end_y, max):
    img = np.zeros((int(size_y / step), int(size_x / step)), dtype=np.uint8)
    for line in lines.decode("utf-8").split("\n"):
        splited = line.split(" ")
        if len(splited) != 3:
            print(splited)
            continue
        img[int(int(splited[1]) / step)][int(int(splited[0]) / step)] = int(float(splited[2]) / max * 255)
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


if __name__ == '__main__':
    tar_info, file = read_tarinfo(sys.argv[1])
    dir_name = sys.argv[1].replace(".tar.gz", "")
    # TODO read size_x size_y ...
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)
    for tf in tar_info:
        # TODO check file pattern
        print("Processing {}".format(tf))
        content, isErr = read(file, tf)
        if isErr:
            continue
        output_png(tf.name.replace(".txt", ".png"), content)
