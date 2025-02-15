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
#include "shared_mutexes.hpp"

std::vector<std::string> get_user_details(const std::string& user_details);

std::unordered_map<std::string, std::array<std::string,2>> get_users();

std::unordered_map<std::string, std::string> get_user_test();

int store_users(std::vector<user_struct> users);

std::string generate_salt();

std::string hash_password(const char *password);

bool authenticate(const std::string& username, const std::string& password);

#endif //IM_AUTH_H
