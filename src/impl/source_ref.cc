using namespace std;
#include "source_ref.h"

//source_ref implementation
source_ref::source_ref(source_ref* other) {
    this->content = other->content;
    this->line_num = other->line_num;
    this->column_num = other->column_num;
    this->file_path = other->file_path;
}

source_ref::source_ref(string content, int line_num, int column_num, string file_path) {
    this->content = content;
    this->line_num = line_num;
    this->column_num = column_num;
    this->file_path = file_path;
}

string source_ref::get_file_path() {
    return this->file_path;
}

string source_ref::get_content() {
    return this->content;
}

int source_ref::get_line_num() {
    return this->line_num;
}

int source_ref::get_column_num() {
    return this->column_num;
}

string source_ref::toString() {
    return this->file_path + ":" + to_string(this->line_num) + ":" + to_string(this->column_num);
}

void source_ref::to_json(json& j) const {
    j = json{
        {"file_path", file_path},
        {"line_num", line_num},
        {"column_num", column_num},
        {"content", content}
    };
}

void source_ref::set_column_num(int column_num) {
    this->column_num = column_num;
}

void source_ref::set_line_num(int line_num) {
    this->line_num = line_num;
}

//source_block implementation

source_block::source_block(vector<source_ref> refs) {
    this->refs = refs;
    this->block_size = 0;
    for (auto& ref : refs) {
        this->block_size += ref.get_content().size();
    }
    this->it = block_iterator(this);
}

uint source_block::get_lines_size() {
    return this->refs.size();
}

source_ref source_block::get_ref(uint index){
    return this->refs[index];
}

block_iterator source_block::get_iterator() {
    return this->it;
}

//block_iterator implementation
block_iterator::block_iterator() {
    this->block = nullptr;
    this->source_ref_index = 0;
    this->char_index = 0;
}

block_iterator::block_iterator(source_block *block) {
    this->block = block;
    this->source_ref_index = 0;
    this->char_index = 0;
}


bool block_iterator::has_next() {
    //depending on the internal implementation of G++/Clang get_content just to get size could be bad performance
    if (char_index < block->get_ref(source_ref_index).get_content().size())
        return true;
    if (source_ref_index < block->get_lines_size())
        return true;
    return false;
}

bool block_iterator::has_prev() {\
    if (char_index > 0)
        return true;
    if (source_ref_index > 0)
        return true;
    return false;
};

char block_iterator::prev() {
    if (!has_prev()) {
        throw runtime_error("No previous characters to iterate over");
    }
    string curr_line = block->get_ref(source_ref_index).get_content();

    if (char_index > 0)
        return curr_line[--char_index];

    curr_line = block->get_ref(--source_ref_index).get_content();
    char_index = curr_line.size() - 1;
    return curr_line[char_index];
}

char block_iterator::next() {
    if (!has_next()) {
        throw runtime_error("No more characters to iterate over");
    }   
    string curr_line = block->get_ref(source_ref_index).get_content();

    if (char_index + 1 < curr_line.size())
        return curr_line[++char_index];
    
    curr_line = block->get_ref(++source_ref_index).get_content();
    char_index = 0;
    return curr_line[char_index];
}

source_ref block_iterator::current_ref(){
    source_ref actual_ref = block->get_ref(source_ref_index);
    source_ref current = source_ref(&actual_ref);
    current.set_column_num(char_index);
    return current;
}