uname -a
whoami
nvidia-smi
mkdir /output/sim/
cp -r world_cone_waveguide /output/sim/world_cone_waveguide
ls -la
cp -r postprocessing /output/sim/postprocessing
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
cd /output/sim

for a in $(seq $1 10 $2)
do
        for i in $(seq $3 0.5 $4)
        do
                python3 -m world_cone_waveguide.main --lam_px=100 --n_core=3 --sig_shell=5 --d_lam=${i} --alpha=${a} --num=10000 --type=TM
                cd cone_v1_d=${i}_a=${a}_lam=100_n=3.0_sig=5.0
                FDTD_Solver config.txt
                cd ..
                tar zcvf cone_v1_d=${i}_a=${a}_lam=100_n=3.0_sig=5.0.tar.gz cone_v1_d=${i}_a=${a}_lam=100_n=3.0_sig=5.0
                python3 -m postprocessing.main --tar_name=cone_v1_d=${i}_a=${a}_lam=100_n=3.0_sig=5.0.tar.gz --d_lam=${i} --lam=100
                tar zcvf images_cone_v1_d=${i}_a=${a}_lam=100_n=3.0_sig=5.0.tar.gz images_cone_v1_d=${i}_a=${a}_lam=100_n=3.0_sig=5.0
                rm -rf cone_v1_d=${i}_a=${a}_lam=100_n=3.0_sig=5.0
        done
done
