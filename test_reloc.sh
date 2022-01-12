#!/bin/bash
tot=0
n=0
for file in $(ls Examples_loader/*.o)
do
  err=0

  echo $file :
  echo -------------------------------------------------
  (readelf -r $file > std)
  (./read_elf -r $file > cstm)

  for word in $(cat std)
  do
    if [[ $word != *"Sym"* ]] && [[ $word != *"Name"* ]] && [[ $word != *"entr"* ]]
    then
      echo $word >> std_l
    fi
  done

  for mot in $(cat cstm)
  do
    if [[ $mot != *"Sym"* ]] && [[ $mot != *"Name"* ]] && [[ $mot != *"entr"* ]]
    then
      echo $mot >> cstm_l
    fi
  done
  echo comparaison output standard et custom...
  diff -w cstm_l std_l > diffout
  for line in $(cat diffout)
  do
    err=$(($err+1))
    echo $line
    echo ERROR
  done

  if [[ $err -ne 0 ]]
  then
    tot=$(($tot+1))
    echo test failed
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
echo parmi $n tests, $tot echecs
