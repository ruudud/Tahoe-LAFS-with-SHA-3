time1=`date +%s.%N`
for file in $files; do
    tahoe cp $file tahoe: > /dev/null
done
time2=`date +%s.%N`
echo $time2 - $time1 | bc > ./logs/$ftype\_totaltime.txt
