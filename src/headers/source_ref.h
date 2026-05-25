#pragma once
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


using namespace std;

class source_ref {
    string content;
    string file_path;
    int line_num;
    int column_num;


public: 
    source_ref(string content, int line_num, int column_num, string file_path);
    //getters
    string get_file_path();
    string get_content();
    int get_line_num();
    int get_column_num();

    //format: file_path:line_num:column_num
    string toString();

    //to json
    void to_json(json& j) const;
};
class source_block;

class block_iterator {
    source_block* block;
    uint source_ref_index;
    uint char_index;
public: 
    block_iterator();
    block_iterator(source_block *block);
    bool has_next();
    char next();
    source_ref current_ref();
    int current_index();
};

class source_block {
    vector<source_ref> refs;
    uint block_size;
    block_iterator it;
public:
    source_block(vector<source_ref> refs);
    uint get_lines_size();
    source_ref get_ref(uint index);
    block_iterator get_iterator();
};

