#!/bin/bash
for cand in `ls run-sha3-multi-4`; do
    time_sh=`cat run-sha3-multi-7/$cand/1gb_tshp.txt`
    numerator=0
    for r in `seq 4 7`; do
        cd run-sha3-multi-$r
        new_num=`cat $cand/1gb_totaltimeput.txt`
        numerator=$(echo $numerator + $new_num | bc -q)
        cd ..
    done;
    result=$(echo "scale=2; $numerator / 4" | bc -q)
    difference=$(echo $result - $time_sh | bc -q)
    diff_sub=${difference:0:6}
    timesh_sub=${time_sh:0:5}
    echo -e "$cand & $result\0163 & $timesh_sub\0163 & $diff_sub\0163 \\\\\ \\hline"
done;
