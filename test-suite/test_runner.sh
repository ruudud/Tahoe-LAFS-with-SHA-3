#!/bin/bash
# This is the main test runner.
# Requires that the grid is up and running, and
# that there exists an tahoe alias named 'tahoe'

file_types=(1b 1kb 1mb 100mb 1gb)

for ftype in ${file_types[*]}; do
    mkdir /tmp/$ftype
    echo '' > /tmp/time_spent_hashing_put
    echo '' > /tmp/time_spent_hashing_get

    files=`ls $ftype*`

    for file in $files; do
        #tahoe cp $file tahoe:
        echo $file
    done

    cp /tmp/time_spent_hashing_put ./$ftype\_tshp.txt

    for file in $files; do
        #tahoe get $file > /dev/null
        #tahoe cp $file /tmp/$ftype/$file
        echo $file
    done

    cp /tmp/time_spent_hashing ./$ftype\_tshg.txt
done
