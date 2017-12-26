import numpy as np


def generate_surface(y_size, delta_x, grain_size):
    wing_size = 12 * grain_size
    noise = np.random.random(y_size + wing_size) * 2 * delta_x - delta_x
    noise = noise / np.max(noise) * delta_x
    gauss = np.fromfunction(lambda i: np.exp(
        (i - 3 * grain_size) / (2 * grain_size ^ 2)), (6 * grain_size,), dtype=int)
    gauss_small = np.fromfunction(lambda i: np.exp(
        (i - 9) / 8), (18,), dtype=int)
    res = np.convolve(noise, gauss)
    res = res / np.max(res)
    res = np.convolve(res, gauss_small)
    print(np.max(res), delta_x,
          np.max(res[wing_size:y_size + wing_size] / np.max(res) * delta_x))
    return res[wing_size:y_size + wing_size] / np.max(res) * delta_x


def check_surface(x, y, x_0, delta_x, surface, n_high):
    if x_0 - delta_x < x < x_0 + delta_x:
        if x > (x_0 + surface[y]):
            return n_high
        elif x < (x_0 + surface[y]):
            return 1
    else:
        if x > x_0:
            return n_high
        elif x < x_0:
            return 1
    return 1
