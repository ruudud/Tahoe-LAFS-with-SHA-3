#!/bin/bash

# generate_random(bytes, number_of_bytes, filename)
function generate_random () {
    dd if=/dev/urandom bs=$1 count=$2 2>/dev/null 1>$3.tv
}

# Generate 1000 files with size of 1 byte
for i in `seq 1 1000`;
do
    generate_random 1c 1 1b_$i
done

# Generate 100 files with size of 1 kilobyte
for i in `seq 1 100`;
do
    generate_random 1K 1 1kb_$i
done

# Generate 50 files with size of 1 megabyte
for i in `seq 1 50`;
do
    generate_random 1M 1 1mb_$i
done

# Generate 5 files with size of 100 megabytes
for i in `seq 1 5`;
do
    generate_random 1M 100 100mb_$i
done

# Generate 1 file with size of 1 gigabyte
generate_random 1G 1 1gb
