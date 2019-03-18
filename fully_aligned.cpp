#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <string>

using namespace std;

int main(int argc, const char *argv[]){
    
    ofstream fastq_file;
    ifstream aligned_reads, input_fq;

    string read_file_name = string(argv[1]);

    string input_fastq = read_file_name.substr(0, read_file_name.find(".")) + ".fastq";   
    string aligned_reads_file = read_file_name.substr(0, read_file_name.find(".")) + ".aligned.txt";   
    string output_fastq = read_file_name.substr(0, read_file_name.find(".")) + ".bwa.fastq";     

    string stt1, stt2, stt3, stt4, stt5;
    string file_2_read;
    
    input_fq.open(input_fastq);
    aligned_reads.open(aligned_reads_file);
    fastq_file.open(output_fastq);

    while (input_fq >> stt1 >> stt2 >> stt3 >> stt4 >> stt5){
        aligned_reads >> file_2_read;
        fastq_file << stt1 << " " << stt2 << endl << file_2_read << endl << stt4 << endl << stt5 << endl;
    }

    aligned_reads.close();
    fastq_file.close();
    input_fq.close();

    return 0;
}
