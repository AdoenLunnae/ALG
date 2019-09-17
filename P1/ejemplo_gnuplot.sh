#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "grafico.eps"
set key right bottom
set xlabel "N(elements)"
set ylabel "t(microseconds)"
plot 'Datos.txt' using 1:2 t "Datos", 'Estimacion.txt' using 1:2 t "Estimacion" w l, 'Medias.txt' using 1:2 t "Medias" with points
_end_
