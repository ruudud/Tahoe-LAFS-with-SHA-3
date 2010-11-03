#!/bin/bash
# This is the main test runner.
# Requires that the grid is up and running, and
# that there exists an tahoe alias named 'tahoe'

file_types=(1b 1kb 1mb 100mb 1gb)

for ftype in ${file_types[*]}; do
    echo '0' > /tmp/time_spent_hashing
    echo '0' > /tmp/number_of_hashops

    files=`ls $ftype*`
    total=`ls $ftype* | wc -l`

    counter=1
    for file in $files; do
        tahoe cp $file tahoe: > /dev/null
        echo $ftype '-get: ' $counter '/' $total
        let counter=counter+1
    done

    cp /tmp/time_spent_hashing ./$ftype\_tshp.txt
    cp /tmp/number_of_hashops ./$ftype\_nohashopsp.txt
    echo '0' > /tmp/time_spent_hashing
    echo '0' > /tmp/number_of_hashops

    counter=1
    for file in $files; do
        tahoe cp tahoe:$file /tmp/$ftype/$file > /dev/null
        echo $ftype '-put: ' $counter '/' $total
        let counter=counter+1
    done

    cp /tmp/time_spent_hashing ./$ftype\_tshg.txt
    cp /tmp/number_of_hashops ./$ftype\_nohashopsg.txt
done
