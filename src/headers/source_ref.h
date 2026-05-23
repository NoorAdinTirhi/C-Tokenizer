#include <string>
#include <vector>

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
};