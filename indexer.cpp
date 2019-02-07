#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string.h>
#include <sdsl/suffix_arrays.hpp>
#include <sdsl/lcp.hpp>
#include <sdsl/bit_vectors.hpp>
#include <climits>

using namespace std;
using namespace sdsl;

int main(int argc, const char * argv[]) {

  unsigned long long vector_size = 1024L*1024L*1024L*1024L;
  cout << "Olusuyor" << endl;
  bit_vector unique_keys = bit_vector(vector_size, 0);
  ifstream uniques;
  uniques.open("strings.txt");
  string key;
  cout << vector_size << endl;
  unsigned long long counter = 0;

  while (uniques >> key){

    unsigned long long indx = 0;
    unsigned long long incr = 0;
    unsigned long long cof = 4;
    
    for (int i = 0; i < key.length(); i++){
      
      if (key[i] == 'A') {
        incr = 0;
      } else if (key[i] == 'C') {
        incr = 1;
      } else if (key[i] == 'G') {
        incr = 2;
      } else if (key[i] == 'T') {
        incr = 3;
      }

      indx = cof*indx + incr;
    }

    if (counter == 100000000){
      cout << "100.000.000 completed" << endl;
      counter = 0;
    } 

    counter++;

    if (indx < vector_size) 
      unique_keys[indx] = 1;

    //cout << indx << " " << unique_keys[indx] << endl;
  }

  store_to_file(unique_keys, "keys.vec");
  uniques.close();

  return 0;
}
