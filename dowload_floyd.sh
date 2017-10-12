#!/usr/bin/env bash

DATA_PATH=$5
OUTPUT_DIR=$6

for a in $(seq $1 10 $2)
do
    for i in $(seq -f %.1f $3 1.0 $4)
    do
        wget -P ${OUTPUT_DIR} \
            https://www.floydhub.com/viewer/data/${DATA_PATH}/sim/cone_v1_d=${i}_a=${a}_lam=100_n=3.0_sig=5.0.tar.gz
    done
done