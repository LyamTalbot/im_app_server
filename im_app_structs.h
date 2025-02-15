//
// Created by Lyam Talbot on 5/2/2025.
//

#ifndef IM_APP_STRUCTS_H
#define IM_APP_STRUCTS_H
#include <string>
#include <vector>

struct user_struct {
    std::string username;
    std::string pw_hash;
    std::string salt;
    std::vector<std::string> messages;
};



#endif //IM_APP_STRUCTS_H
