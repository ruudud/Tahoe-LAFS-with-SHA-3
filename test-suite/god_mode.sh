
# For hver funksjon
#   Oppdatere alle klienter
#   Skifte til riktig hash-function
#   Starte noder osv. 
#   Starte testing

for i in sha256 blake  bmw  cubehash  echo  fugue  groestl  hamsi \
    jh  keccak  luffa  shabal  shavite3  simd  skein;
do
    cd /home/eiriha/tahoe-svn/scripts/
    ./do_it_all.sh $i
    cd /home/eiriha/Tahoe-LAFS-with-SHA-3/test-suite/
    ./test_runner.sh
    mkdir $i
    mv log/*.txt $i/
done

