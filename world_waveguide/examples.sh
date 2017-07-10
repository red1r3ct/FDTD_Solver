#! /bin/sh

python3 -m world_waveguide.gen_world \
    --size_x 3000 \
    --size_y 3000 \
    --lam 0.6 \
    --len 1000 \
    --x 200 \
    --y 1500 \
    --pix 100 \
    --d_core 100 \
    --d_shell 200 \
    --n_core 3 \
    --n_shell 1.5
