#include "reader.h"

reader* reader::instance;

reader* reader::get_instance(string file_path) {
    if (reader::instance == nullptr){
        instance = new reader(file_path);
    }
    return reader::instance;
}

reader::reader(string file_path) {
    this->file_path = file_path;
    file.open(file_path);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + file_path);
    }
}
reader::~reader() {
    file.close();
}

void reader::read_file() {
    int line_num = 1;
    string line;
    while(getline(file, line)){
        refs.push_back(source_ref(line, line_num, 0, file_path));
        line_num++;
    }
}

vector<source_ref> reader::get_refs() {
    return refs;
}