#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <string>

using namespace std;

int main(int argc, const char *argv[]){
    
    ifstream sam_file;
    ofstream aligned_reads;

    string read_file_name = string(argv[1]);

    string sam_file_name = read_file_name.substr(0, read_file_name.find(".")) + ".mem.sam";
    string align_name = read_file_name.substr(0, read_file_name.find(".")) + ".aligned.txt";    

    string stt;
    
    aligned_reads.open(align_name);
    sam_file.open(sam_file_name);

    while (sam_file >> stt){
        if (stt.length() == 101){
            if (stt.find_first_not_of("ACGTN") != string::npos){
                continue;
            } else {
                aligned_reads << stt << endl;
            }
        }  
    }

    aligned_reads.close();
    sam_file.close();

    return 0;
}
