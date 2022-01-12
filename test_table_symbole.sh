#!/bin/bash
tot=0
n=0
for file in $(ls Examples_loader/*.o)
do
  err=0

  echo $file :
  echo -------------------------------------------------
  (readelf -s $file > std)
  (./read_elf -s $file > cstm)

  for word in $(cat std)
  do
    echo $word >> std_l
  done

  for mot in $(cat cstm)
  do
    echo $mot >> cstm_l
  done
  diff cstm_l std_l > diffout

  for line in $(cat diffout)
  do  
    echo $line # ligne a effacer si affichage plus concis souhaite
    if [[ $line != ">" ]] && [[ $line != "."*  ]] && [[ $line != [0-9]*a[0-9]* ]]
    then
      echo ERROR
      err=$(($err+1))
    fi
  done

  if [[ err -ne 0 ]]
  then
    echo NOK
    tot=$(($tot+1))
  else
    echo OK
  fi

  n=$(($n+1))

  rm std
  rm cstm
  rm std_l
  rm cstm_l
  rm diffout
done
echo parmi $n tests, $tot echouent
