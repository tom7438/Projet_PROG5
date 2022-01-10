n=0
t=0
for file in $(ls Examples_loader/*.o)
do (readelf -h $file > out_standard_readelf)
(./read_elf -h $file > out_our_readelf)
diff -w out_standard_readelf out_our_readelf && echo $file : bonne lecture de l\'entete #|| (echo $file : mauvaise lecture de l\'entete && n=$(($n+1)) )
if [ $? -eq 1 ]
then echo $file : mauvaise lecture de l\'entete && n=$(($n+1))
fi
t=$(($t+1))
rm out_standard_readelf
rm out_our_readelf
done
echo out of $t tests, $n failed
