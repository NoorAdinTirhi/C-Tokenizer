#include <string>
using namespace std;

class expected_token_exception : public std::exception {
    string message;
    int error_code;
public:
    expected_token_exception(string message, int error_code);
    
    const char* what() const noexcept override {
        return message.c_str();
    }
    
    int get_error_code() const {
        return error_code;
    }
};