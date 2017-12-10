import math


def generate_config(base_path, size_x, size_y, type, num, lam_px, x_sphere):
    i_big_out_first_x = 0
    i_big_out_last_x = size_x
    i_big_step = 10
    i_big_out_first_y = 0
    i_big_out_last_y = size_y

    start_time = 0
    end_time = num
    step_time = int(lam_px * math.sqrt(2) * 2)

    i_small_out_first_x = int(x_sphere)
    i_small_out_last_x = int(x_sphere + lam_px * 15)
    i_small_step = 1
    i_small_out_first_y = int(15 * lam_px)
    i_small_out_last_y = int(size_y - 15 * lam_px)

    conf = '''SimulationType: {type}
Grid{type}: {size_x} {size_y}
Epsilon: epsilon.txt
BoundaryCond: ABC
BoundaryCond: TFSF {tfsf_first_x} {tfsf_last_x} {tfsf_first_y} {tfsf_last_y} Harmonic 1 {lam_px}
Output: Intensity i_big {i_big_out_first_x} {i_big_out_last_x} {i_big_step} {i_big_out_first_y} {i_big_out_last_y} {i_big_step} {start_time} {end_time} {step_time} 0
Output: Intensity i_small {i_small_out_first_x} {i_small_out_last_x} {i_small_step} {i_small_out_first_y} {i_small_out_last_y} {i_small_step} {start_time} {end_time} {step_time} 0
Run: {num}
'''.format(
    type=type,
    size_x=size_x,
    size_y=size_y,
    num=num,
    lam_px=lam_px,
    tfsf_first_x=100,
    tfsf_last_x=size_x - 100,
    tfsf_first_y=100,
    tfsf_last_y=size_y - 100,
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
