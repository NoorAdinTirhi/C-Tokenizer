#include "invocations.h"

config_manager* config_manager::options;
unordered_map<string, string> config_manager::flags;

config_manager* config_manager::get() {
    if (options == nullptr)
        throw invalid_argument("config manager not initialized yet");
    return options;
}


config_manager::config_manager(){
    //check necessary flags
    if (flags["i"] == "" or\
        flags["o"] == ""){
        throw invalid_argument("need to at least name an input file '-i <file_path>' and an output file '-o <file_path>'");
    }

    input_file_name = flags["i"];
    output_file_name = flags["o"];
}

string config_manager::get_in_file_name(){
    return this->input_file_name;
}

string config_manager::get_out_file_name(){
    return this->output_file_name;
}

void config_manager::init(int argc, char* argv[]){
    unordered_map<string, string> args;

    init_flag_map();

    string curr_flag = "";
    string curr_string;
    for (int i = 1; i < argc; i++){
        curr_string = string(argv[i]);
        if (curr_flag == ""){
            if (curr_string.size() < 2) throw invalid_argument("invalid flag : " + curr_string + ", flag format is -<flag_name>");
            if (curr_string[0] != '-') throw invalid_argument("specify flags with the char '-' as prefix");

            curr_string = curr_string.substr(1);
            if (flags.find(curr_string) == flags.end()) throw invalid_argument("unrecognized flag " + curr_string);
            curr_flag = curr_string;
        }else{
            flags[curr_flag] = curr_string;
            curr_flag = "";
        }
    }

    options = new config_manager();
}


void config_manager::init_flag_map() {
    flags = {
        {"i", ""},
        {"o", ""}
    };
}