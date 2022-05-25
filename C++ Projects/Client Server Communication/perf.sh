#!/bin/bash

#######################################################################
#
# Copyright (C) 2018-2022 David C. Harrison. All right reserved.
#
# You may not use, distribute, publish, or modify this code without 
# the express written permission of the copyright holder.
#
#######################################################################

if [ "$#" -ne 1 ]; then
  echo "USAGE: ./perf.sh numbers"
  exit;
fi
num=$1

capped() {
  num=$1
  lists=$2
  cores=$3

  ./radix $num $lists $cores -p > radix.single &
  pid=$!

  cmax=0
  while true
  do
    cat /proc/$pid/status > radix.threads 2>/dev/null
    status=$?
    if [ $status -ne 0 ]
    then
      break
    fi

    grep "Generate time:" radix.single >/dev/null
    if [ $? -eq 0 ]
    then
      # if [ $cmax -eq 0 ]; then
      #   sleep 0.5
      # fi
      threads=`cat radix.threads | grep Threads | awk '{print $2'}`
      cmax=$(( threads > cmax ? threads : cmax ))
      echo -n .
    else
      echo -n -
    fi
    sleep 0.02

  done

  echo ""
  echo -n "Capped $lists lists $cores cores: "
  fail=`grep FAIL radix.single | wc -l`
  pass=`grep PASS radix.single | wc -l`

  if [[ fail -gt 0 ]]
  then
    echo "FAIL ( native )"
  else
    if [[ pass -gt 0 ]]
    then
      (( cmax -= 2 ))
      if [ $cmax -le $cores ]
      then
        echo "PASS"
      else
        echo "FAIL ( too many cores: $cmax, should have been no more than $cores )"
      fi
    else
      echo "FAIL ( functional )"
    fi
  fi
}

for lists in 1 2 3 
do
  (( cores = lists * 1 ))
  capped $num $lists $cores
done

for lists in 1 2 3 
do
  (( cores = lists * 2 ))
  capped $num $lists $cores
done

for lists in 1 2 3 
do
  (( cores = lists * 3 ))
  capped $num $lists $cores
done

rm radix.single radix.quad radix.threads 2>/dev/null
