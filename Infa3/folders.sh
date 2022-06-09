#!/bin/bash
main_catalogs={'Katalog_A','Katalog_B','Katalog_C','Katalog_z'}


if [ $# -eq 0 ]
  then
     echo "No arguments supplied, please write: folders.sh arg1 arg2 where arg1 -> folders, arg2 -> subfolders"
  else
START_CATALOG=A
STOP_CATALOG=$1
START_SUBC=1
STOP_SUBC=$2

for catalog in $(eval echo {$START_CATALOG..$STOP_CATALOG})
do
mkdir ${catalog}
for subcatalog in $(eval echo {$START_SUBC..$STOP_SUBC})
do
mkdir ${catalog}/${subcatalog}
done
done
fi



