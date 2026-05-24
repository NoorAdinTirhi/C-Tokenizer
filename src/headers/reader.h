#include <iostream>
#include <fstream>
#include "source_ref.h"
#include <stdexcept>

using namespace std;

class reader {
    string file_path;
    ifstream file;
    vector<source_ref> refs;

    public:
    reader(string file_path);
    ~reader();
    void read_file();
    vector<source_ref> get_refs();
};