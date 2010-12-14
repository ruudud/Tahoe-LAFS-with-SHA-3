#!/bin/bash
for op in put get; do
    if [ "$op" == "put" ]; then
        tsh_file="$1_tshp.txt"
        totaltime_file="$1_totaltimeput.txt"
    else
        tsh_file="$1_tshg.txt"
        totaltime_file="$1_totaltimeget.txt"
    fi
    echo "$op:"
    for cand in `ls run-sha3-multi-4`; do
        time_sh=`cat run-sha3-multi-7/$cand/$tsh_file`
        numerator=0
        for r in `seq 4 7`; do
            cd run-sha3-multi-$r
            new_num=`cat $cand/$totaltime_file`
            numerator=$(echo $numerator + $new_num | bc -q)
            cd ..
        done;
        result=$(echo "scale=2; $numerator / 4" | bc -q)
        difference=$(echo $result - $time_sh | bc -q)
        diff_sub=${difference:0:6}
        timesh_sub=${time_sh:0:5}
        fraction=$(echo "scale=2; $time_sh * 100 / $result" | bc -q)
        echo -e "$cand & $result\0163 & $timesh_sub\0163 & $diff_sub\0163 & $fraction\\% \\\\\ \\hline"
    done;
done;
