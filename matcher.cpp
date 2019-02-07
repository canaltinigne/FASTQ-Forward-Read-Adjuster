#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <string>
#include <chrono>

using namespace std;

#define ull unsigned long long int

int main(int argc, const char *argv[]){
    
    ifstream aligned_file, fastq_output;
    ofstream results;

    string read_file_name = string(argv[1]);

    string align_name = read_file_name.substr(0, read_file_name.find(".")) + ".aligned.txt";    
    string fastq_output_name = read_file_name.substr(0, read_file_name.find(".")) + ".fastq.out";
    string stt;
    
    fastq_output.open(fastq_output_name);
    aligned_file.open(align_name);
    results.open("match_results.txt");

    double counter = 0, trues = 0;

    string wrd1, wrd2, wrd3, wrd4, wrd5;
    
    while (fastq_output >> wrd1 >> wrd2 >> wrd3 >> wrd4 >> wrd5) {
        aligned_file >> stt;
        counter++;

        if (wrd3 == stt) 
            trues++;
    }

    results << "Matching completed..." << endl << trues << " of " << counter << " reads are matched." << endl << "Matching rate: " << trues/counter << endl;
   
    fastq_output.close();
    aligned_file.close();
    results.close();

    return 0;
}
