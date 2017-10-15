# -*- coding: utf-8 -*-
from .helpers.waveguide import check_point as check_point_core
from .helpers.waveguide_shell import check_point as check_point_shell
from .helpers.dielectric_wall import check_point as check_point_dielectric_wall
from .helpers.output import output_array_to_file, output_sig_eps_png

import argparse
import math
import os


def write_eps(x_0, y_0, length, d, delta_x_px, size_x, size_y, n_core, base_path):
    eps = []
    print('Start processing epsilon')
    for y in range(size_y):
        print('Processing [{}/{}]'.format(y, size_y - 1), end="\r")
        for x in range(size_x):
            if check_point_core(x - x_0, y - y_0, d, length, delta_x_px):
                eps.append(n_core)
            else:
                eps.append(1)
    print('Finish processing epsilon')
    output_array_to_file(eps, base_path + '/epsilon.txt', size_x)
    return eps


def write_sig(x_0, y_0, length, d, d_shell, size_x, size_y, sig_shell, base_path):
    sig = []
    print('Start processing sigma')
    for y in range(size_y):
        print('Processing [{}/{}]'.format(y, size_y - 1), end="\r")
        for x in range(size_x):
            if check_point_dielectric_wall(x - x_0, y - y_0, d_shell, 400):
                sig.append(sig_shell)
            else:
                sig.append(0)
    print('Finish processing sigma')
    output_array_to_file(sig, base_path + '/sigma.txt', size_x)
    return sig

def write_excluded(x_0, y_0, length, d, d_shell, size_x, size_y, base_path):
    excluded = []
    print('Start processing excluded')
    for y in range(size_y):
        print('Processing [{}/{}]'.format(y, size_y - 1), end="\r")
        for x in range(size_x):
            if check_point_shell(x - x_0, y - y_0, d, d_shell, length):
                excluded.append(1)
            else:
                excluded.append(0)
    print('Finish processing excluded')
    output_array_to_file(excluded, base_path + '/excluded.txt', size_x)
    return excluded


def write(lam_px, n_core, sig_shell, d_over_lam, delta_x, num, sim_type):
    length = int(20 * lam_px)
    delta_x_px = delta_x * d_over_lam * lam_px
    d_shell = int(d_over_lam * lam_px + 2 * lam_px)
    size_x = int(25 * lam_px + length)
    size_y = int(10 * lam_px + d_shell)
    x_0 = int(10 * lam_px)
    y_0 = int(size_y / 2)
    base_path = './sphere_v1_d={d_over_lam}_del={delta_x}_lam={lam_px}_n={n_core}_sig={sig_shell}'.format(
        d_over_lam=d_over_lam,
        delta_x=delta_x,
        lam_px=lam_px,
        n_core=n_core,
        sig_shell=sig_shell
    )
    if not os.path.exists(base_path):
        os.makedirs(base_path)
    eps = write_eps(x_0, y_0, length, d_over_lam * lam_px, delta_x_px, size_x, size_y, n_core, base_path)
    sig = write_sig(x_0, y_0, length, d_over_lam * lam_px, d_shell, size_x, size_y, sig_shell, base_path)
    write_excluded(x_0, y_0, length, d_over_lam * lam_px, d_shell, size_x, size_y, base_path)
    write_conf(sim_type, x_0 - 10 * lam_px, y_0, lam_px, size_x, size_y, num, base_path)
    output_sig_eps_png(eps, sig, base_path + "/world", sig_shell, size_x, size_y)


def write_conf(sim_type, x_source, y_source, lam_px, size_x, size_y, num, base_path):
    i_big_out_first_x = 0
    i_big_out_last_x = size_x
    i_big_step = 5
    i_big_out_first_y = 0
    i_big_out_last_y = size_y

    start_time = 0
    end_time = num
    step_time = int(lam_px * math.sqrt(2) * 2)

    i_small_out_first_x = int(20 * lam_px)
    i_small_out_last_x = size_x
    i_small_step = 1
    i_small_out_first_y = 0
    i_small_out_last_y = size_y

    conf = '''SimulationType: {type}
Grid{type}: {size_x} {size_y}
Epsilon: epsilon.txt
Sigma: sigma.txt
Excluded: excluded.txt
BoundaryCond: ABC
Output: Intensity i_big {i_big_out_first_x} {i_big_out_last_x} {i_big_step} {i_big_out_first_y} {i_big_out_last_y} {i_big_step} {start_time} {end_time} {step_time} 0
Output: Intensity i_small {i_small_out_first_x} {i_small_out_last_x} {i_small_step} {i_small_out_first_y} {i_small_out_last_y} {i_small_step} {start_time} {end_time} {step_time} 0
Source: Harmonic 1 {lam_px} {x_source} {y_source}
Run: {num}
'''.format(
        type=sim_type,
        size_x=size_x,
        size_y=size_y,
        num=num,
        lam_px=lam_px,
        x_source=x_source,
        y_source=y_source,
        i_big_out_first_x=i_big_out_first_x,
        i_big_out_last_x=i_big_out_last_x,
        i_big_step=i_big_step,
        i_big_out_first_y=i_big_out_first_y,
        i_big_out_last_y=i_big_out_last_y,
        start_time=start_time,
        end_time=end_time,
        step_time=step_time,
        i_small_out_first_x=i_small_out_first_x,
        i_small_out_last_x=i_small_out_last_x,
        i_small_step=i_small_step,
        i_small_out_first_y=i_small_out_first_y,
        i_small_out_last_y=i_small_out_last_y,
    )

    f = open(base_path + '/config.txt', 'w')
    f.write(conf)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--lam_px", help="Number of pixels per wavelength")
    parser.add_argument("--n_core", help="Refractive index of waveguide core")
    parser.add_argument("--sig_shell", help="Sigma of waveguide shell")
    parser.add_argument("--d_lam", help="Waveguide diameter in lambda")
    parser.add_argument("--delta_x", help="Distance between sphere center and straight part ending in diameters")
    parser.add_argument("--num", help="Number of iterations")
    parser.add_argument("--type", help="Simulation type (TE|TM)")
    args = parser.parse_args()
    lam_px = int(args.lam_px)
    num = int(args.num)
    n_core = float(args.n_core)
    sig_shell = float(args.sig_shell)
    d_lam = float(args.d_lam)
    delta_x = float(args.delta_x)
    sim_type = args.type
    write(lam_px, n_core, sig_shell, d_lam, delta_x, num, sim_type)

# python3 main.py --lam_px=100 --n_core=3 --sig_shell=5 --d_lam=0.3 --delta_x=2 --num=20000 --type=TM
