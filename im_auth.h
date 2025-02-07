//
// Created by Lyam Talbot on 5/2/2025.
//

#ifndef IM_AUTH_H
#define IM_AUTH_H
#include <vector>
#include "im_app_structs.h"
#include <fstream>
#include <ostream>
#include <sstream>

user_struct create_user_struct(const std::string& user_details);

std::vector<user_struct> get_users();

int store_users(std::vector<user_struct> users);

std::string generate_salt();

std::string hash_password(const char *password);

bool authenticate(const char *username, const char *password);

#endif //IM_AUTH_H
