import tarfile, sys
from PIL import Image


def output_png(lines):
    # list_of_px = []
    print(lines.decode("ascii"))
    # for line in lines.decode("utf-8"):
    #     print(line)
    # im = Image.new('L', (size_x, size_y))
    # im.putdata(list_of_px)
    # im.save(filename, 'PNG')


def read_tarinfo(fname):
    tar = tarfile.open(fname)
    return list(tar.getmembers()), tar


def convert_to_png(file, tar_info):
    f = file.extractfile(tar_info)
    content = f.read()
    return content

if __name__ == '__main__':
    tar_info, file = read_tarinfo(sys.argv[1])
    content = convert_to_png(file, tar_info[17])
    output_png(content)


