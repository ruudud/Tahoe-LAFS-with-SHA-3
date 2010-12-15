# For hver funksjon
#   Oppdatere alle klienter
#   Skifte til riktig hash-function
#   Starte noder osv. 
#   Starte testing

mkdir logs
for i in sha256 blake bmw cubehash echo  fugue  groestl  hamsi \
   jh  keccak  luffa  shabal  shavite3  simd  skein;
#for i in blake;
#for i in sha256
do
    cd /home/eiriha/tahoe-svn/scripts/
    ./do_it_all.sh $i
    cd /home/eiriha/Tahoe-LAFS-with-SHA-3/test-suite/
    time=`date +%s.%N`
    time ./test_runner.sh
    time2=`date +%s.%N`
    mkdir $i
    mv logs/*.txt $i/
    echo $time2 - $time | bc
done
