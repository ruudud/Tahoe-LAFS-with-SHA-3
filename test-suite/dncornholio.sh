for i in `seq 1 10`;
do
    folder=run-sha256d-multi-$i
    mkdir $folder
    ./god_mode.sh > $folder/foo.out 2>$folder/foo.err
    for k in sha256 blake bmw cubehash echo fugue groestl hamsi \
        jh keccak luffa shabal shavite3 simd skein;
        do
            mv $k/ $folder/
        done
done
