uname -a
whoami
nvidia-smi
nvcc --version
apt-get update -y
add-apt-repository main
add-apt-repository universe
add-apt-repository restricted
add-apt-repository multiverse
apt-get install -y cmake clang
cmake .
make -j8
cp ./FDTD_Solver /usr/local/bin/FDTD_Solver
mkdir /output/sim/
cp -r world_surface /output/sim/world_surface
cp -r postprocessing /output/sim/postprocessing
cd /output/sim

grain=$3

for del in $(seq $1 0.3 $2)
do
    for n_iter in $(seq 1 1 10)
    do
        python3 -m world_surface.main --lam_px=100 --n_high=1.6 --n_low=1 --delta_x_lam=${del} --grain_lam=${grain} --num=8000 --type=TM --n=${n_iter}
        cd surface_v1_del_x=${del}_lam=100_n=1.6_grain=${grain}_n=${n_iter}
        FDTD_Solver config.txt
        cd ..
        tar zcvf surface_v1_del_x=${del}_lam=100_n=1.6_grain=${grain}_n=${n_iter}.tar.gz surface_v1_del_x=${del}_lam=100_n=1.6_grain=${grain}_n=${n_iter}
        python3 -m postprocessing.main --tar_name=surface_v1_del_x=${del}_lam=100_n=1.6_grain=${grain}_n=${n_iter}.tar.gz --lam=100 --size_x=3000 --size_y=8000 --step=3
    done
done
