#!/bin/bash          

fastq_file="ERR174310_1.fastq"
fastq_output="$fastq_file.out"

./comparator $fastq_file && 
cat results_*.txt > $fastq_output &&
rm results_*.txt
