#include <iostream>
#include "invocations.h"
#include "tokens.h"
#include "reader.h"
#include "fsm.h"

using namespace std;
int main (int argc, char* argv[]) {
    //init config_manager
    config_manager::init(argc, argv);
    config_manager* options = config_manager::get();

    //init maps and sets
    keyword_token::init_keyword_maps();
    operator_token::init_operator_map();
    preprocessor_directive_token::init_directive_map();
    fsm::init_sets();

    reader *r = reader::get_instance(options->get_in_file_name());
    r->read_file();

    source_block block = source_block(r->get_refs());
    fsm f = fsm(&block);
    vector<token*> token_ptrs = f.parse();
    vector<json> js;

    ofstream outFile(options->get_out_file_name());
    for(auto it : token_ptrs){
        json j;
        it->to_json(j);
        js.push_back(j);
    }
    json final_j = js;

    outFile << final_j.dump(4) << endl;
    
    return 0;
}