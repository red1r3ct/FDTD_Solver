import tarfile, sys
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


def convert_to_png(file, tar_info):
    f = file.extractfile(tar_info)
    content = f.read()
    return content

if __name__ == '__main__':
    tar_info, file = read_tarinfo(sys.argv[1])
    content = convert_to_png(file, tar_info[179])
    output_png(content, 4200, 1930, "test.png", 5, 0.01)


