# -*- coding: utf-8 -*-
from .helpers.aspherical_lens import check_point as check_point_asph
from .helpers.spherical_lens import check_point as check_point_sph
from .helpers.dimensions import mm2px
from .helpers.output import output_array_to_file, output_png

size_x = 8000
size_y = 6000
lam = 0.6  # mm
lam_px = 100

n_sph = 3.14
n_asph = 1.5

d_asph = mm2px(15, lam, lam_px)
x_pos_asph = mm2px(2 * lam, lam, lam_px)
y_pos_asph = round(size_y / 2)
diameter_asph = mm2px(25.2, lam, lam_px)

delta = mm2px(5, lam, lam_px)

radius_sph = mm2px(10, lam, lam_px)
d_sph = mm2px(10 - lam / 2, lam, lam_px)
x_pos_sph = x_pos_asph + d_asph + delta
y_pos_sph = round(size_y / 2)

eps = []

print('Start proccessing epsilon')

for y in range(size_y):
    print('Proccessing [{}/{}]'.format(y, size_y - 1), end="\r")
    for x in range(size_x):
        if check_point_asph(x - x_pos_asph, y - y_pos_asph, d_asph, diameter_asph, lam, lam_px):
            eps.append(n_asph)
        elif check_point_sph(x - x_pos_sph, y - y_pos_sph, radius_sph, d_sph, 10000000):
            eps.append(n_sph)
        else:
            eps.append(1)

print('Finish proccessing epsilon')

print('Start writing epsilon')
output_array_to_file(eps, 'epsilon.txt', size_x)
print('Finish writing epsilon')
