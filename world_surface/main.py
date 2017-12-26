# -*- coding: utf-8 -*-
from .helpers.generate_surface import check_surface, generate_surface
from .helpers.output import output_array_to_file, output_sig_eps_png

import argparse
import math
import os


def write_eps(x_0, size_y, size_x, delta_x, grain_size, n_high, base_path):
    eps = []
    surf = generate_surface(size_y, delta_x, grain_size)
    print('Start processing epsilon')
    for y in range(size_y):
        print('Processing [{}/{}]'.format(y, size_y - 1), end="\r")
        for x in range(size_x):
            n = check_surface(x, y, x_0, delta_x, surf, n_high)
            eps.append(n * n)

    print('Finish processing epsilon')
    output_array_to_file(eps, base_path + '/epsilon.txt', size_x)
    return eps


def write(lam_px, n_high, n_low, delta_x, grain_size, num, sim_type, n):
    size_x = int(20 * lam_px)
    size_y = int(70 * lam_px)
    x_0 = int(5 * lam_px)
    y_0 = int(size_y / 2)
    base_path = './surface_v1_del_x={delta_x}_lam={lam_px}_n={n_high}_grain={grain_size}_n={n}'.format(
        delta_x=delta_x,
        lam_px=lam_px,
        n_high=n_high,
        n=n,
        grain_size=grain_size,
    )
    if not os.path.exists(base_path):
        os.makedirs(base_path)
    eps = write_eps(x_0, size_y, size_x, int(delta_x * lam_px),
                    int(grain_size * lam_px), n_high, base_path)
    write_conf(sim_type, x_0 - 10 * lam_px, y_0,
               lam_px, size_x, size_y, num, base_path)
    output_sig_eps_png(eps, [], base_path + "/world", 3, size_x, size_y)


def write_conf(sim_type, x_source, y_source, lam_px, size_x, size_y, num, base_path):
    i_big_out_first_x = 0
    i_big_out_last_x = size_x
    i_big_step = 3
    i_big_out_first_y = 0
    i_big_out_last_y = size_y

    start_time = int(num * 0.7)
    end_time = num
    step_time = int(lam_px * math.sqrt(2) * 2)

    tfsf_first_x = lam_px
    tfsf_last_x = size_x - lam_px
    tfsf_first_y = lam_px
    tfsf_last_y = size_y - lam_px

    conf = '''SimulationType: {type}
Grid{type}: {size_x} {size_y}
Epsilon: epsilon.txt
BoundaryCond: ABC
BoundaryCond: TFSF {tfsf_first_x} {tfsf_last_x} {tfsf_first_y} {tfsf_last_y} Harmonic 1 {lam_px}
Output: Intensity i_big {i_big_out_first_x} {i_big_out_last_x} {i_big_step} {i_big_out_first_y} {i_big_out_last_y} {i_big_step} {start_time} {end_time} {step_time} 0
Run: {num}
'''.format(
        type=sim_type,
        size_x=size_x,
        size_y=size_y,
        num=num,
        lam_px=lam_px,
        i_big_out_first_x=i_big_out_first_x,
        i_big_out_last_x=i_big_out_last_x,
        i_big_step=i_big_step,
        i_big_out_first_y=i_big_out_first_y,
        i_big_out_last_y=i_big_out_last_y,
        start_time=start_time,
        end_time=end_time,
        step_time=step_time,
        tfsf_first_x=tfsf_first_x,
        tfsf_last_x=tfsf_last_x,
        tfsf_first_y=tfsf_first_y,
        tfsf_last_y=tfsf_last_y,
    )

    f = open(base_path + '/config.txt', 'w')
    f.write(conf)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--lam_px", help="Number of pixels per wavelength")
    parser.add_argument("--n_high", help="Refractive index of waveguide core")
    parser.add_argument("--n_low", help="Sigma of waveguide shell")
    parser.add_argument("--delta_x_lam", help="Waveguide diameter in lambda")
    parser.add_argument(
        "--grain_lam", help="Distance between sphere center and straight part ending in diameters")
    parser.add_argument("--num", help="Number of iterations")
    parser.add_argument("--type", help="Simulation type (TE|TM)")
    parser.add_argument("--n", help="Iteration")
    args = parser.parse_args()

    lam_px = int(args.lam_px)
    n_high = float(args.n_high)
    n_low = float(args.n_low)
    delta_x_lam = float(args.delta_x_lam)
    grain_lam = float(args.grain_lam)
    num = int(args.num)
    n = int(args.n)
    sim_type = args.type

    write(lam_px, n_high, n_low, delta_x_lam, grain_lam, num, sim_type, n)
