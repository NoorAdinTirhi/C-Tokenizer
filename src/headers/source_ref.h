#pragma once
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


using namespace std;

struct source_ref {
    string content;
    string file_path;
    int line_num;
    int column_num;


 
    source_ref(source_ref* other);
    source_ref(string content, int line_num, int column_num, string file_path);
    //getters
    string get_file_path();
    string get_content();
    int get_line_num();
    int get_column_num();
    void set_column_num(int column_num);
    void set_line_num(int line_num);

    //format: file_path:line_num:column_num
    string toString();

    //to json
    void to_json(json& j) const;
};
struct source_block;

struct block_iterator {
    source_block* block;
    uint source_ref_index;
    uint char_index;
 
    block_iterator();
    block_iterator(source_block *block);
    bool has_next();
    char next();
    bool has_prev();
    char prev();
    source_ref current_ref();
    int current_index();
};

struct source_block {
    vector<source_ref> refs;
    uint block_size;
    block_iterator it;

    source_block(vector<source_ref> refs);
    uint get_lines_size();
    source_ref get_ref(uint index);
    block_iterator get_iterator();
};

