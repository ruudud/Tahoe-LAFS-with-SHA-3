#!/bin/bash
# This is the main test runner.
# Requires that the grid is up and running, and
# that there exists an tahoe alias named 'tahoe'

mkdir ./logs
file_types=(1b 1kb 1mb 100mb 1gb)
#file_types=(1gb)

for ftype in ${file_types[*]}; do
    mkdir /tmp/$ftype
    echo '0' > /tmp/time_spent_hashing
    echo '0' > /tmp/number_of_hashops
    rm /tmp/data

    files=`ls $ftype*`
    total=`ls $ftype* | wc -l`

    time1=`date +%s.%N`
    counter=1
    for file in $files; do
        tahoe cp $file tahoe: > /dev/null
        echo $ftype '-put: ' $counter '/' $total
        let counter=counter+1
    done
    time2=`date +%s.%N`
    echo $time2 - $time1 | bc > ./logs/$ftype\_totaltimeput.txt

    cp /tmp/time_spent_hashing ./logs/$ftype\_tshp.txt
    cp /tmp/number_of_hashops ./logs/$ftype\_nohashopsp.txt
    echo '0' > /tmp/time_spent_hashing
    echo '0' > /tmp/number_of_hashops
    rm /tmp/data

    time1=`date +%s.%N`
    counter=1
    for file in $files; do
        tahoe cp tahoe:$file /tmp/$ftype/$file > /dev/null
        echo $ftype '-get: ' $counter '/' $total
        let counter=counter+1
    done
    time2=`date +%s.%N`
    echo $time2 - $time1 | bc > ./logs/$ftype\_totaltimeget.txt

    cp /tmp/time_spent_hashing ./logs/$ftype\_tshg.txt
    cp /tmp/number_of_hashops ./logs/$ftype\_nohashopsg.txt
done
