#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
using namespace std;

struct config_manager {
    static config_manager* options;
    static config_manager* get();
    static unordered_map<string,string> flags;

    static void init(int argc, char* argv[]);
    
    string get_in_file_name();
    string get_out_file_name();

    private:
    static void init_flag_map();
    config_manager();
    string input_file_name;
    string output_file_name;
};