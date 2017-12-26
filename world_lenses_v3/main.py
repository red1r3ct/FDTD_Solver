# -*- coding: utf-8 -*-
import argparse
import os

from .helpers.aspherical_lens import check_point as check_point_asph
from .helpers.spherical_lens import check_point as check_point_sph
from .helpers.plate import check_point as check_point_plate
from .helpers.dimensions import mm2px
from .helpers.config import generate_config
from .helpers.output import output_array_to_file, output_png, output_sig_eps_png


parser = argparse.ArgumentParser()
parser.add_argument("--lam_px", help="Number of pixels per wavelength")
parser.add_argument("--delta", help="Distance between sphere and aspheric lens")
parser.add_argument("--sigma_sph", help="Sigma values for lossy simulations of spherical lens")
parser.add_argument("--num", help="Number of iterations")


args = parser.parse_args()
lam_px = int(args.lam_px)
num = int(args.num)
delta = float(args.delta)
sigma_sph = float(args.sigma_sph)

size_x = 8000
size_y = 6000
lam = 0.6  # mm

n_sph = 3.4
n_asph = 1.5

d_asph = mm2px(15, lam, lam_px)
x_pos_asph = mm2px(2 * lam, lam, lam_px)
y_pos_asph = round(size_y / 2)
diameter_asph = mm2px(25.2, lam, lam_px)
lens_sph_f = mm2px(15, lam, lam_px)

radius_sph = mm2px(5, lam, lam_px)
d_sph = mm2px(5 - lam / 2, lam, lam_px)
x_pos_sph = x_pos_asph + d_asph + delta
y_pos_sph = round(size_y / 2)

print('''
  Creating lens 2 with params:
    delta={delta}
    radius_sph={radius_sph}
    d_sph={d_sph}
    x_pos_sph={x_pos_sph}
    y_pos_sph={y_pos_sph}
'''.format(
  delta=delta,
  radius_sph=radius_sph,
  d_sph=d_sph + d_sph - 5 * lam_px,
  x_pos_sph=x_pos_sph,
  y_pos_sph=y_pos_sph,
))

d_plate = lam_px
x_pos_plate = x_pos_sph + d_sph
y_pos_plate = y_pos_sph
size_x_plate = mm2px(0.25, lam, lam_px)
size_y_plate = mm2px(20, lam, lam_px)
n_plate = n_sph

eps = []
sig = []

print('Creating config')
base_path = './lenses_v3_delta={delta}_lam=100'.format(delta=int(delta))
if not os.path.exists(base_path):
    os.makedirs(base_path)
generate_config(
  base_path=base_path,
  size_x=size_x,
  size_y=size_y,
  type='TM',
  num=num,
  x_sphere=x_pos_sph,
  lam_px=lam_px,
)

print('Start proccessing epsilon and sigma')

for y in range(size_y):
    print('Proccessing [{}/{}]'.format(y, size_y - 1), end="\r")
    for x in range(size_x):
        if check_point_asph(x - x_pos_asph, y - y_pos_asph, d_asph, diameter_asph, lam, lam_px):
            eps.append(n_asph)
            sig.append(0)
        elif check_point_sph(x - x_pos_sph, y - y_pos_sph, radius_sph, d_sph, 10000000):
            eps.append(n_sph)
            sig.append(sigma_sph)
        elif check_point_plate(x - x_pos_plate, y - y_pos_plate, size_x_plate, size_y_plate):
            eps.append(n_plate)
            sig.append(sigma_sph)
        else:
            eps.append(1)
            sig.append(0)


output_sig_eps_png(eps, sig, "./world", 4, size_x, size_y)

print('Finish proccessing epsilon')

print('Start writing epsilon')
output_array_to_file(eps, base_path + '/epsilon.txt', size_x)
print('Finish writing epsilon')
print('Start writing sigma')
output_array_to_file(sig, base_path + '/sigma.txt', size_x)
print('Finish writing sigma')
