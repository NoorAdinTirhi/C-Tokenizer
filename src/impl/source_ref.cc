using namespace std;

#include "source_ref.h"

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