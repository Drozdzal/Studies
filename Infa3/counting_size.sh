#!/bin/bash
rozmiar_wszystkich=0
rozmiar_fila=0
path_to_cp='/home/drozdzal/Desktop/Infa3/pierwszy'
for file in k*
do
echo ${file}
rozmiar_fila=$(eval "du -b ${file} | cut -f1")
rozmiar_wszystkich=$((rozmiar_wszystkich+rozmiar_fila))
cp ${file} ${path_to_cp}/${file}
done
echo "size of all files is equal to ${rozmiar_wszystkich}"
