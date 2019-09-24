#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "grafico.eps"
set key right bottom
set xlabel "N"
set ylabel "t(microseconds)"
plot 'Datos.txt' using 1:2 t "Datos", 'Datos.txt' using 1:3 t "Estimacion" w l
_end_
