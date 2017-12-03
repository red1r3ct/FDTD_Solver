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
cp -r world_sphere_waveguide /output/sim/world_sphere_waveguide
cp -r postprocessing /output/sim/postprocessing
cd /output/sim

for del in $(seq $1 0.2 $2)
do
        for i in $(seq $3 0.5 $4)
        do
                python3 -m world_sphere_waveguide.main --lam_px=100 --n_core=3 --sig_shell=5 --d_lam=${i} --delta_x=${del} --num=10000 --type=TM
                cd sphere_v1_d=${i}_del=${del}_lam=100_n=3.0_sig=5.0
                FDTD_Solver config.txt
                cd ..
                tar zcvf sphere_v1_d=${i}_del=${del}_lam=100_n=3.0_sig=5.0.tar.gz sphere_v1_d=${i}_del=${del}_lam=100_n=3.0_sig=5.0
                python3 -m postprocessing.main --tar_name=sphere_v1_d=${i}_del=${del}_lam=100_n=3.0_sig=5.0.tar.gz --d_lam=${i} --lam=100
                rm -rf sphere_v1_d=${i}_del=${del}_lam=100_n=3.0_sig=5.0
        done
done
