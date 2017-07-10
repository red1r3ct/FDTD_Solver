import argparse
from .helpers.dimensions import mm2px, px2mm
from .helpers.flat_waveguide import FlatWaveguide
from .helpers.output import output_array_to_file, output_png

parser = argparse.ArgumentParser()
parser.add_argument("--pix", type=int, help="pixels in wavelength")
parser.add_argument("--lam", type=float, help="Wavelength in mm")
parser.add_argument("--x", type=int, help="X position of left center point")
parser.add_argument("--y", type=int, help="Y position of left center point")
parser.add_argument("--len", type=int, help="Length of waveguide")
parser.add_argument("--d_shell", type=int, help="Diameter of shell")
parser.add_argument("--d_core", type=int, help="Diameter of core")
parser.add_argument("--n_core", type=float, help="Refractive index of core")
parser.add_argument("--n_shell", type=float, help="Refractive index of shell")
parser.add_argument("--size_x", type=int, help="Size X of area")
parser.add_argument("--size_y", type=int, help="Size Y of area")
args = parser.parse_args()

size_x = args.size_x
size_y = args.size_y
lam = args.lam
lam_px = args.pix
x0 = args.x
y0 = args.y
d_core = args.d_core
d_shell = args.d_shell
length = args.len
n_core = args.n_core
n_shell = args.n_shell

waveguide = FlatWaveguide(x0, y0, d_core, d_shell, length)

eps = []

print('Start proccessing epsilon')

for y in range(size_y):
    print('Proccessing [{}/{}]'.format(y, size_y - 1), end="\r")
    for x in range(size_x):
        if waveguide.is_core(x, y):
            eps.append(n_core)
        elif waveguide.is_shell(x, y):
            eps.append(n_shell)
        else:
            eps.append(1)

print('Finish processing epsilon')
print('Start writing epsilon')

output_png(eps, 'epsilon.png', 4, size_x, size_y)

print('Finish writing epsilon')
