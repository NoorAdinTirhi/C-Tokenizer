#include <iostream>
#include <fstream>
#include "source_ref.h"
#include <stdexcept>

using namespace std;

class reader {
    static reader *instance;
    string file_path;
    ifstream file;
    vector<source_ref> refs;

    reader(string file_path);
    ~reader();

    public:
    static reader* get_instance(string file_path); 
    void read_file();
    vector<source_ref> get_refs();
};