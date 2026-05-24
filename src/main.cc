#include <iostream>

#include "reader.h"

using namespace std;
int main () {
    reader *r = reader::get_instance("test/test.c");
    r->read_file();
    
    for (auto ref : r->get_refs()){
        // json temp = json();
        // ref.to_json(temp);
        // cout << temp.dump(4) << endl;
        cout << ref.toString() << " " << ref.get_content() << endl;
    }
    return 0;
}