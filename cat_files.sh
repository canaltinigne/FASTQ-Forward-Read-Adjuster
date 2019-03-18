#!/bin/bash          

cat results_1.txt results_2.txt results_3.txt > res_123.txt &
cat results_4.txt results_5.txt results_6.txt > res_456.txt &
cat results_7.txt results_8.txt results_9.txt > res_789.txt &
cat results_10.txt results_11.txt results_12.txt > res_10s.txt &
wait
rm results_*.txt
wait
cat res_123.txt res_456.txt > resu_1.txt &
cat res_789.txt res_10s.txt > resu_2.txt &
wait
rm res_*.txt &
wait
cat resu_1.txt resu_2.txt > ERR174310_2.fastq.out &
wait
rm resu_*.txt 