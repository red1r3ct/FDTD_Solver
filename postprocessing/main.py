import argparse

from .gen_png import main_internal

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--lam_px", help="Number of pixels per wavelength")
    parser.add_argument("--size_x", help="Image size x")
    parser.add_argument("--size_y", help="Image size y")
    parser.add_argument("--tar_name", help="Name of a tarfile to open")
    parser.add_argument("--step", help="Pixels steps")
    args = parser.parse_args()

    lam_px = int(args.lam_px)
    tar_name = str(args.tar_name)
    size_x = str(args.size_x)
    size_y = str(args.size_y)
    step = str(args.step)

    print("Start processing images: size_x={size_x} size_y={size_y} \n".format(
        size_x=size_x,
        size_y=size_y,
    ))

    main_internal(tar_name, 0, size_x, step, 0, size_y, step, 0, 0)
