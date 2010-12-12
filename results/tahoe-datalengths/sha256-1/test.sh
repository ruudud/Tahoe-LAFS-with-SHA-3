ftypes=(1b 1kb 1mb 100mb 1gb)
ops=(p g)
file_sizes=(63 101 106 65569 131106)


echo "file operation total 63per 101per 106per 65569per 131106per"
for op in ${ops[*]};
do
    for i in ${ftypes[*]};
        do
            file=$i"_data"$op".txt"
            s=`cat $file | wc -l`
            k="$i && $s"
            for fs in ${file_sizes[*]};
            do
                #echo $fs $file
                line="^"$fs"$ "$file
                t=`grep $line | wc -l`
                u=`echo "scale=2; 100*$t / $s" | bc`
                #k=$k" && "$u
                k=$k" "$u
            done
            #echo $k "\\""\\"" \hline"
            echo $k
        done
done
