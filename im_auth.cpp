//
// Created by Lyam Talbot on 5/2/2025.

#include "im_auth.h"

#include <iostream>
#include <random>
#include <utility>
#include <__random/random_device.h>
//


std::vector<std::string> get_user_details(const std::string& user_details) {
    user_struct_t new_user;
    std::istringstream iss(user_details);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

user_struct_t create_new_user(std::string username, std::string password) {
    user_struct_t new_user;
    new_user.username = std::move(username);
    new_user.pw_hash = std::move(password);
    new_user.salt = generate_salt();
    return new_user;
}

/*
 * Open a file
 * Get a line that contains the user's information
 * Parse it and create a user struct.
 * Store in a vector of users
 */

//Replace vector of users with an unordered_map?
//std::unordered_map<std::string, std::string[]>
std::unordered_map<std::string, std::array<std::string, 2>> get_users() {
    std::unordered_map<std::string, std::array<std::string, 2>> user_map;
    std::fstream database;
    database_mutex.lock_shared();
    database.open("users.txt");
    // std::vector<user_struct> users;
    if (database.is_open()) {
        std::string line;
        std::getline(database, line); //clear the first line
        while (std::getline(database, line)) {
            std::vector<std::string> user_tokens = get_user_details(line);
            user_map[user_tokens[0]] = { user_tokens[0], user_tokens[1] };
        }
    } else {
        throw std::runtime_error("Unable to open database file");
    }
    database.close();
    database_mutex.unlock_shared();
    return user_map;
}


int store_users(std::vector<user_struct_t> users) {
    std::fstream database;
    database_mutex.lock();
    database.open("users.txt", std::ios::out);
    if (database.is_open()) {
        //TODO: Store users as comma separated values
        //Need to put in a header that describes what the values are
        //Loop through the vector and print one line to the file for each
        database << "username,password,salt" << std::endl;
        for (auto & user : users) {
            database << user.username << "," << user.pw_hash << "," << user.salt << std::endl;
            if (database.fail()) {
                database_mutex.unlock();
                std::cerr << "Unable to write to database file" << std::endl;
                return -1;
            }
        }
    } else {
        database_mutex.unlock();
        std::cerr << "Unable to open database file" << std::endl;
        return -1;
    }
    return 0;
}

std::string generate_salt() {
    static std::random_device random_device;
    static std::mt19937 generator(random_device());
    static std::uniform_int_distribution<int> distribution(33, 126);
    std::string salt;
    int i = 0;
    for (i = 0; i < 6; i++) {
        salt.push_back(static_cast<char>(distribution(generator)));
    }
    return salt;
}

bool authenticate(const std::string& username, const std::string& password) {
    std::unordered_map<std::string, std::array<std::string, 2>> users = get_users();
    return true;
}