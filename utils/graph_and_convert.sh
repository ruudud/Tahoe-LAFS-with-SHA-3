#!/bin/bash
if [ -z "$1" ]; then 
    echo usage: $0 directory
    exit
fi

python results_to_graphs.py -d $1
cd $1

for fn in `ls *.svg`; do
    echo "Converting $fn to PDF."
    inkscape -D -T -z --file=$fn --export-pdf=`echo $fn | sed s/svg//`pdf
done
