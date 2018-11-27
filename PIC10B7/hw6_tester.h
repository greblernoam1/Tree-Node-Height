#include "hw6.h"
#include <fstream>

using std::endl;
using std::ofstream;

int main(){
    ofstream fout;
    fout.open("data.txt");
    for ( int n = 0 ; n < 5 ; n++ ){
        fout << n << "\t" << compute_average_height(n) << endl;
    }
    
    fout.close();
    return 0;
}