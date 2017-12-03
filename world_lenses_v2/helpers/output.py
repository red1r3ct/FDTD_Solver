# -*- coding: utf-8 -*-
from PIL import Image


def output_array_to_file(arr, filename, size_x):
    f = open(filename, 'w')
    for i in range(len(arr)):
        x = i % size_x
        y = int(i / size_x)
        f.write(' '.join([str(x), str(y), str(arr[i])]) + '\n')
    f.close()


def output_png(arr, filename, max_val, size_x, size_y):
    list_of_px = []
    for px in arr:
        list_of_px.append(int(float(px) / max_val * 255))
    im = Image.new('L', (size_x, size_y))
    im.putdata(list_of_px)
    im.save(filename, 'PNG')

def output_png(arr, filename, max_val, size_x, size_y):
    list_of_px = []
    for px in arr:
        list_of_px.append(int(float(px) / max_val * 255))
    im = Image.new('L', (size_x, size_y))
    im.putdata(list_of_px)
    im.save(filename, 'PNG')


def output_sig_eps_png(eps, sig, filename, max_val, size_x, size_y):
    print("Creating world images at " + filename)
    eps_list_of_px = []
    for px in eps:
        eps_list_of_px.append(int(float(px) / max_val * 255))
    im = Image.new('L', (size_x, size_y))
    im.putdata(eps_list_of_px)
    im.save(filename + "_eps.png", 'PNG')
    sig_list_of_px = []
    for px in sig:
        sig_list_of_px.append(int(float(px) / max_val * 255))
    im = Image.new('L', (size_x, size_y))
    im.putdata(sig_list_of_px)
    im.save(filename + "_sig.png", 'PNG')
    print("World images created")