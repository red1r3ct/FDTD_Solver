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
cp -r world_lenses_v2 /output/sim/world_lenses_v2
cp -r postprocessing /output/sim/postprocessing
cd /output/sim

for del in $(seq $1 100 $2)
do
    python3 -m world_lenses_v2.main --lam_px=100 --delta=${del} --num=30000
    cd lenses_v2_delta=${del}_lam=100
    FDTD_Solver config.txt
    cd ..
    tar zcvf lenses_v2_delta=${del}_lam=100.tar.gz lenses_v2_delta=${del}_lam=100
    python3 -m postprocessing.main --tar_name=lenses_v2_delta=${del}_lam=100.tar.gz --lam=100 --size_x=8000 --size_y=6000 --step=10
    rm -rf lenses_v2_delta=${del}_lam=100
done
