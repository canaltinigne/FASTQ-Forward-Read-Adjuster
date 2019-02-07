#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string.h>
#include <sdsl/suffix_arrays.hpp>
#include <sdsl/lcp.hpp>
#include <sdsl/bit_vectors.hpp>
#include <algorithm>
#include <string>
#include <thread>
#include <chrono>
#include <stdlib.h>

using namespace std;
using namespace sdsl;

vector<string> all_reads;
bit_vector unique_keys;

#define ull unsigned long long int

void writer_threads(ull start, ull end, int order, vector<string>& first_line, vector<string>& third_line, vector<string>& fourth_line){
    ofstream results;
    string output_name = string("results_") + to_string(order) + string(".txt");
    results.open(output_name);

    for (ull qq = start; qq < end; qq++) {
        results << first_line[qq] << endl << all_reads[qq] << endl << third_line[qq] << endl << fourth_line[qq] << endl;
    }

    results.close();
}

void compare_thread(ull start, ull end) {

    ull and_number = 1099511627775L;
    ull value[96] = {0};
    value['C'] = 1;
    value['G'] = 2;
    value['T'] = 3;

    for (ull ind = start; ind < end; ind++) {
        string read = all_reads[ind];
        int read_len = read.length();
        int i = 0;
        ull val = 0;
        int step = 0;
        long reverse_count = 0;
    
        string rev_read = read;
        reverse(rev_read.begin(), rev_read.end());
        
        for (long j = 0; j < read_len; j++) {
            char ch = rev_read[j];

            if (ch == 'A') rev_read[j] = 'T';
            else if (ch == 'T') rev_read[j] = 'A';
            else if (ch == 'G') rev_read[j] = 'C';
            else if (ch == 'C') rev_read[j] = 'G';
        }

        while ((step < 20) && (i < read_len)){
            if (read[i] == 'N'){
                val = 0;
                i += 1;
                step = 0;
            }
            else {
                val = val * 4 + value[read[i]];
                step++;
                i++;
            }
        }

        while (i < read_len) {
            reverse_count += unique_keys[val];

            if (read[i] != 'N') {
                val = ((val * 4 + value[read[i]]) & and_number);
                i++;
            }
            else {
                val = 0;
                step = 0;

                while ((step < 20) && (i < read_len)) {
                    if (read[i] == 'N') {
                        val = 0;
                        i += 1;
                        step = 0;
                    }
                    else {
                        val = val * 4 + value[read[i]];
                        step++;
                        i++;
                    }
                }
            }
        }

        i = 0;
        val = 0;
        step = 0;
        long forward_count = 0;

        while ((step < 20) && (i < read_len)){
            if (rev_read[i] == 'N'){
                val = 0;
                i += 1;
                step = 0;
            }
            else {
                val = val * 4 + value[rev_read[i]];
                step++;
                i++;
            }
        }

        while (i < read_len) {
            forward_count += unique_keys[val];

            if (rev_read[i] != 'N') {
                val = ((val * 4 + value[rev_read[i]]) & and_number);
                i++;
            }
            else {
                val = 0;
                step = 0;

                while ((step < 20) && (i < read_len)) {
                    if (rev_read[i] == 'N') {
                        val = 0;
                        i += 1;
                        step = 0;
                    }
                    else {
                        val = val * 4 + value[rev_read[i]];
                        step++;
                        i++;
                    }
                }
            }
        }

        //cout << "Forward: " << forward_count << " - Reverse: " << reverse_count << endl;

        if (reverse_count > forward_count) {
            all_reads[ind] = rev_read;
        }
    }   
}

int main(int argc, const char *argv[]){
    
    chrono::high_resolution_clock::time_point st = chrono::high_resolution_clock::now();
    
    load_from_file(unique_keys, "keys.vec");
    ofstream results;
    results.open("results.txt");
    vector<string> first_line;
    vector<string> third_line;
    vector<string> fourth_line;
    results << "Reading Keys Bit Vector " << endl;

    ifstream reads;
    string read_file_name = string(argv[1]);
    reads.open(read_file_name);
    string output_name = read_file_name + ".out";

    string word1, word2, word3, word4, word5;
    chrono::high_resolution_clock::time_point en = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = en-st;

    results << "Reading Keys Bit Vector finished in " << diff.count() << " seconds." << endl;

    st = chrono::high_resolution_clock::now();
    results << "FASTQ file is read..." << endl;

    while (reads >> word1 >> word2 >> word3 >> word4 >> word5){
        all_reads.push_back(word3);
        first_line.push_back(word1 + " " + word2);
        third_line.push_back(word4);
        fourth_line.push_back(word5);
    } 

    en = chrono::high_resolution_clock::now();
    diff = en-st;
    results << "FASTQ file read in " << diff.count() << " seconds." << endl;

    int num_threads = 12;
    thread t[num_threads];
    ull vec_size = all_reads.size();

    results << "Comparison starts..." << endl;
    st = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < num_threads; ++i) {
        t[i] = thread(compare_thread, i*vec_size/num_threads, (i+1)*vec_size/num_threads);
    }

    for (int i = 0; i < num_threads; ++i) t[i].join();

    en = chrono::high_resolution_clock::now();
    diff = en-st;
    results << "Comparison finished in " << diff.count() << " seconds." << endl;

    results << "Creating FASTQ output" << endl;

    st = chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        t[i] = thread(writer_threads, i*vec_size/num_threads, (i+1)*vec_size/num_threads, i+1, ref(first_line), ref(third_line), ref(fourth_line));
    }

    for (int i = 0; i < num_threads; ++i) t[i].join();

    en = chrono::high_resolution_clock::now();
    diff = en-st;
    results << "FASTQ output created in " << diff.count() << " seconds." << endl;
    
    results.close();
    reads.close();
    
    return 0;
}
