#!/bin/bash
fail=0
fich=0
for file in $(ls Examples_loader/*.o)
do
echo $file :
echo ----------------------------------------------------
(readelf -S $file > out_std_sh) #standard
(./read_elf -S $file > out_cstm_sh) #notre readelf
n=4
m=2
err=0
while  [ "$(sed -n ${n}p out_std_sh)" != "Key to Flags:" ]
do
strs=$(sed -n ${n}p out_std_sh | tr -d ' ')
strc=$(sed -n ${m}p out_cstm_sh | tr -d ' ' | tr -d '\t')

if [[ "$strc" != "$strs" ]]
then
  echo $strs
  echo $strc
  echo ERROR!!
  if [[ "strs"=="*[...]*" ]]
  then
    echo resolving conflict...
    strs=$(sed -n ${n}p out_std_sh | cut -d' ' -f 6- | tr -d ' ')
    strc=$(sed -n ${m}p out_cstm_sh | cut -d' ' -f 6- | tr -d ' ' | tr -d '\t')
    if [[ "$strc" == "$strs" ]]
    then
      echo $strs
      echo $strc
      echo conflict resolved.
    else
      err=$(($err+1))
      echo conflict unresolved
    fi
  else
    err=$(($err+1))
 fi
fi
n=$(($n+1))
m=$(($m+1))
done
echo parmi les $(($n-4)) sections, $err different
echo
if [[ $err -ne 0 ]]
then
fail=$(($fail+1))
fi
fich=$(($fich+1))
rm out_std_sh
rm out_cstm_sh
done
echo $fich tests realises, $fail echecs
