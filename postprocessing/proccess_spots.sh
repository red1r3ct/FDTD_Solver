for del in $(seq $1 100 $2)
do
    python3 -m FDTD_Solver.postprocessing.calculate_spot --out_name=test --t_start=28000 --t_end=30000 --tar_file=lenses_v2_delta=${del}_lam=100.tar.gz --th1=0.5 --th2=0.86 --ext=pdf
done
