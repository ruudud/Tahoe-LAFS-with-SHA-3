
# For hver funksjon
#   Oppdatere alle klienter
#   Skifte til riktig hash-function
#   Starte noder osv. 
#   Starte testing

for i in blake  bmw  cubehash  echo  fugue  groestl  hamsi \
    jh  keccak  luffa  shabal  shavite3  simd  skein;
do
    /home/eiriha/tahoe-svn/scripts/do_it_all.sh $i
    ./test_runner.sh
done

