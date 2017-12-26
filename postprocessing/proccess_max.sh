grain=$3

for del in $(seq $1 0.3 $2)
do
    for n_iter in $(seq 1 1 10)
    do
        python3 -m FDTD_Solver.postprocessing.calculate_max --out_name=test --t_start=5000 --t_end=8000 --tar_file=surface_v1_del_x=${del}_lam=100_n=1.6_grain=${grain}_n=${n_iter}.tar.gz
    done
done
