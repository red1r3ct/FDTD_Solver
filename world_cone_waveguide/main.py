# -*- coding: utf-8 -*-
from .helpers.waveguide import check_point as check_point_core
from .helpers.waveguide_shell import check_point as check_point_shell
from .helpers.output import output_array_to_file

import argparse
import math
import os


def write_eps(x_0, y_0, length, d, alpha, size_x, size_y, n_core, base_path):
    eps = []
    print('Start processing epsilon')
    for y in range(size_y):
        print('Processing [{}/{}]'.format(y, size_y - 1), end="\r")
        for x in range(size_x):
            if check_point_core(x - x_0, y - y_0, d, length, alpha):
                eps.append(n_core)
            else:
                eps.append(1)
    print('Finish processing epsilon')
    output_array_to_file(eps, base_path + '/epsilon.txt', size_x)


def write_sig(x_0, y_0, length, d, d_shell, size_x, size_y, sig_shell, base_path):
    sig = []
    print('Start processing sigma')
    for y in range(size_y):
        print('Processing [{}/{}]'.format(y, size_y - 1), end="\r")
        for x in range(size_x):
            if check_point_shell(x - x_0, y - y_0, d, d_shell, length):
                sig.append(sig_shell)
            else:
                sig.append(0)
    print('Finish processing sigma')
    output_array_to_file(sig, base_path + '/sigma.txt', size_x)


def write(lam_px, n_core, sig_shell, d_over_lam, alpha, num, sim_type):
    length = int(10 * lam_px)
    d_shell = int(d_over_lam * lam_px + 8 * lam_px)
    size_x = int(26 * lam_px + length)
    size_y = int(10 * lam_px + d_shell)
    x_0 = int(10 * lam_px)
    y_0 = int(size_y / 2)
    base_path = './cone_v1_d={d_over_lam}_a={alpha_deg}_lam={lam_px}_n={n_core}_sig={sig_shell}'.format(
        d_over_lam=d_over_lam,
        alpha_deg=( alpha * 180 / math.pi ),
        lam_px=lam_px,
        n_core=n_core,
        sig_shell=sig_shell
    )
    if not os.path.exists(base_path):
        os.makedirs(base_path)
    write_eps(x_0, y_0, length, d_over_lam * lam_px, alpha, size_x, size_y, n_core, base_path)
    write_sig(x_0, y_0, length, d_over_lam * lam_px, d_shell, size_x, size_y, sig_shell, base_path)
    write_conf(sim_type, x_0 - 10 * lam_px, y_0, lam_px, size_x, size_y, num, base_path)

def write_conf(sim_type, x_source, y_source, lam_px, size_x, size_y, num, base_path):
    i_big_out_first_x = 0
    i_big_out_last_x = size_x
    i_big_step = 5
    i_big_out_first_y = 0
    i_big_out_last_y = size_y

    start_time = 0
    end_time = num
    step_time = int(lam_px * math.sqrt(2))

    i_small_out_first_x = 0
    i_small_out_last_x = size_x
    i_small_step = 1
    i_small_out_first_y = 0
    i_small_out_last_y = size_y

    conf = '''SimulationType: {type}
GridTE: {size_x} {size_y}
Epsilon: epsilon.txt
Sigma: sigma.txt
BoundaryCond: ABC
Output: Intensity i_big {i_big_out_first_x} {i_big_out_last_x} {i_big_step} {i_big_out_first_y} {i_big_out_last_y} {i_big_step} {start_time} {end_time} {step_time} 1
Output: Intensity i_small {i_small_out_first_x} {i_small_out_last_x} {i_small_step} {i_small_out_first_y} {i_small_out_last_y} {i_small_step} {start_time} {end_time} {step_time} 1
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
    parser.add_argument("--alpha", help="Cone angle in degrees")
    parser.add_argument("--num", help="Number of iterations")
    parser.add_argument("--type", help="Simulation type (TE|TM)")
    args = parser.parse_args()
    lam_px = int(args.lam_px)
    num = int(args.num)
    n_core = float(args.n_core)
    sig_shell = float(args.sig_shell)
    d_lam = float(args.d_lam)
    alpha = float(args.alpha) / 180.0 * math.pi
    sim_type = args.type
    write(lam_px, n_core, sig_shell, d_lam, alpha, num, sim_type)

# python 3 main.py --lam_px=100 --n_core=3 --sig_shell --d_lam=0.3 --alpha=180 --num=20000 --type=TM
