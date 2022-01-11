#!/bin/bash
if [[ $# -lt 1 ]]
then
echo "usage: ./test_cntenu_section -x [n°][section]"
else
  p=0
  tot=0
  for file in $(ls Examples_loader/*.o)
  do
    p=$(($p+1))
    (readelf $* $file > out_std )
    (./read_elf $* $file > out_cstm )
    err=0
    echo $file :
    echo ---------------------------------------------------------

    n=1
    arr="$(sed -n ${n}p out_std)"
    while [[ $arr != *"0x"* ]] && [[ $arr != *"no data"* ]] && [[ "$(sed -n 1p out_cstm | tr -d ' ')" != *"No"* ]]
    do
      n=$(($n+1))
      arr="$(sed -n ${n}p out_std)"
    done

    m=1
    arr2="$(sed -n ${m}p out_cstm)"
    while [[ $arr2 != *"0x"* ]] && [[ $arr != *"no data"* ]] && [[ $arr2 != *"No"* ]]
    do
      m=$(($m+1))
      arr2="$(sed -n ${m}p out_cstm)"
    done

    if [[ "$arr" == *"no data"* ]] || [[ "$arr2" == *"No section"* ]]
    then
      echo No data
      echo OK
      echo
      rm out_std
      rm out_cstm
      continue
    fi

    strs="$(sed -n ${n}p out_std | rev | cut -c 17- | rev | tr -d ' ' )"
    strc="$(sed -n ${m}p out_cstm | tr -d ' ')"

    while [[ "$strs" == *"0x"* ]]
    do
      echo $strs
      echo $strc
      if [[ $strc == $strs ]]
      then
        echo OK
      else
        err=$(($err+1))
      fi
      n=$(($n+1))
      m=$(($m+1))
      strs=$(sed -n ${n}p out_std | rev | cut -c 17- | rev | tr -d ' '  )
      strc=$(sed -n ${m}p out_cstm | tr -d ' ')
    done

    rm out_std
    rm out_cstm
    if [[ $err -ne 0 ]]
    then
    tot=$(($tot+1))
    echo Error!
    fi
    echo
  done
echo parmi $p tests, $tot ont echoue



fi
