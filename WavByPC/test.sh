#!/bin/bash

echo -n ">"
read fn
if( ./a.out $fn) then
  echo "Program Complete"
  else
      echo "Program Fail"
      fi
