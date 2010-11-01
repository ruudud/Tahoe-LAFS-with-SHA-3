#!/bin/bash
# This is the main test runner.
# Requires that the grid is up and running, and
# that there exists an tahoe alias named 'tahoe'

file_types=(1b 1kb 1mb 100mb 1gb)

for ftype in ${file_types[*]}; do
    files=`ls $ftype*`
    mkdir /tmp/$ftype

    for file in $files; do
        #tahoe put $file
        echo $file
    done

    for file in $files; do
        #tahoe cp tahoe:$file /tmp/$ftype/$file
        echo $file
    done
done
