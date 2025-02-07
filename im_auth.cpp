//
// Created by Lyam Talbot on 5/2/2025.

#include "im_auth.h"

#include <iostream>
#include <random>
#include <utility>
#include <__random/random_device.h>
//


user_struct create_user_struct(const std::string& user_details) {
    user_struct new_user;
    std::istringstream iss(user_details);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }
    new_user.username = tokens[0];
    new_user.pw_hash = tokens[1];
    new_user.salt = tokens[2];
    return new_user;
}

user_struct create_new_user(std::string username, std::string password) {
    user_struct new_user;
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
std::vector<user_struct> get_users() {
    std::fstream database;
    read_mutex.lock();
    database.open("users.txt");
    std::vector<user_struct> users;
    if (database.is_open()) {
        std::string line;
        std::getline(database, line); //clear the first line
        while (std::getline(database, line)) {
            user_struct new_user = create_user_struct(line);
            users.push_back(new_user);
        }
    } else {
        throw std::runtime_error("Unable to open database file");
    }
    database.close();
    read_mutex.unlock();
    return users;
}

int store_users(std::vector<user_struct> users) {
    std::fstream database;s
    write_mutex.lock();
    database.open("users.txt", std::ios::in);
    if (database.is_open()) {
        //TODO: Store users as comma separated values
        //Need to put in a header that describes what the values are
        //Loop through the vector and print one line to the file for each
    } else {
        write_mutex.unlock();
        throw std::runtime_error("Unable to open database file");
    }
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