#!/bin/bash          

fastq_file="ERR174310_1.fastq"
fastq_output="$fastq_file.out"

./comparator $fastq_file && 
mmv -a results_2.txt results_1.txt &&
mmv -a results_3.txt results_1.txt &&
mmv -a results_4.txt results_1.txt &&
mmv -a results_5.txt results_1.txt &&
mmv -a results_6.txt results_1.txt &&
mmv -a results_7.txt results_1.txt &&
mmv -a results_8.txt results_1.txt &&
mmv -a results_9.txt results_1.txt &&
mmv -a results_10.txt results_1.txt &&
mmv -a results_11.txt results_1.txt &&
mmv -a results_12.txt results_1.txt &&
mv results_1.txt $fastq_output && 
rm results_*.txt