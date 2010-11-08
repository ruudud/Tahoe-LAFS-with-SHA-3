
# For hver funksjon
#   Oppdatere alle klienter
#   Skifte til riktig hash-function
#   Starte noder osv. 
#   Starte testing

mkdir logs
for i in blake sha256 bmw  cubehash  echo  fugue  groestl  hamsi \
    jh  keccak  luffa  shabal  shavite3  simd  skein;
do
    cd /home/eiriha/tahoe-svn/scripts/
    ./do_it_all.sh $i
    cd /home/eiriha/Tahoe-LAFS-with-SHA-3/test-suite/
    ./test_runner.sh
    mkdir $i
    mv logs/*.txt $i/
done

