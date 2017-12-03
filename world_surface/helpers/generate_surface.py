import numpy as np


def generate_surface(y_size, delta_x, grain_size):
    noise = np.random.random(y_size) * 2 * delta_x - delta_x
    gauss = np.fromfunction(lambda i: np.exp((i-3*grain_size)/(2*grain_size^2)), 6*grain_size, dtype=int)
    return np.convolve(noise, gauss)


def check_surface(x, y, x_0, delta_x, surface, n_high, n_low):
    if x_0 - delta_x < x < x_0 - delta_x:
        if x > (x_0 + surface[y]):
            return n_high
        else x < (x_0 + surface[y]):
            return n_low
    else:
        if x > x_0:
            return n_high
        else: x < x_0:
            return n_low
