#include <iostream>
#include "tokens.h"
#include "reader.h"
#include "fsm.h"

using namespace std;
int main () {
    //init maps and sets
    keyword_token::init_keyword_maps();
    operator_token::init_operator_map();
    preprocessor_directive_token::init_directive_map();
    fsm::init_sets();

    reader *r = reader::get_instance("test/test.c");
    r->read_file();

    source_block block = source_block(r->get_refs());
    fsm f = fsm(&block);
    vector<token*> token_ptrs = f.parse();
    vector<json> js;

    ofstream outFile("test/ref/test.log");
    for(auto it : token_ptrs){
        json j;
        it->to_json(j);
        js.push_back(j);
    }
    json final_j = js;

    outFile << final_j.dump(4) << endl;
    
    return 0;
}