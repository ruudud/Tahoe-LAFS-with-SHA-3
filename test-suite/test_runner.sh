#!/bin/bash
# This is the main test runner.
# Requires that the grid is up and running, and
# that there exists an tahoe alias named 'tahoe'

file_types=(1b 1kb 1mb 100mb 1gb)

for ftype in ${file_types[*]}; do
    echo '0' > /tmp/time_spent_hashing
    echo '0' > /tmp/number_of_hashops

    files=`ls $ftype*`

    for file in $files; do
        tahoe cp $file tahoe:
    done

    cp /tmp/time_spent_hashing ./$ftype\_tshp.txt
    cp /tmp/number_of_hashops ./$ftype\_nohashopsp.txt
    echo '0' > /tmp/time_spent_hashing
    echo '0' > /tmp/number_of_hashops

    for file in $files; do
        #tahoe get $file > /dev/null
        tahoe cp tahoe:$file /tmp/$ftype/$file
    done

    cp /tmp/time_spent_hashing ./$ftype\_tshg.txt
    cp /tmp/number_of_hashops ./$ftype\_nohashopsg.txt
done
