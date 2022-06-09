#!/bin/bash
max_size=0
size_of_file=0

for i in *
do

x="du -b ${i} | cut -f1"
x2="du -b ${i} |cut -f2"
size_of_file=$(eval "$x")
 

 if [[ ${size_of_file} -gt ${max_size} ]]
  then
    max_size=${size_of_file}
    nazwa=$(eval "$x2")
  else
    echo "kurde tamten wiekszy"
  fi

done
echo "Najwiekszy pliczek ma rozmiar :${max_size}"
echo "Jewo nazwa to ${nazwa}" 

