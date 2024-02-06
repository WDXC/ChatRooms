#ifndef STRUCT_H_
#define  STRUCT_H_

#include <string>

typedef struct tagLogin {
    std::string userid;
    std::string password;

    public:
    tagLogin() {}
    tagLogin(std::string fir_param, std::string sec_param) 
        : userid(fir_param),
        password(sec_param)
    {}

} *PLogin, Login;

#endif

