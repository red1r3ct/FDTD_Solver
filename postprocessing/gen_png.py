import tarfile
import sys
import os
import scipy.misc
import numpy as np


def output_png(lines, size_x, size_y, filename, step, max):
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
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)
    for tf in tar_info:
        print("Processing {}".format(tf))
        content, isErr = read(file, tf)
        if isErr:
            continue
        output_png(content, 20000, 10000, tf.name.replace(".txt", ".png"), 5, 0.02)
