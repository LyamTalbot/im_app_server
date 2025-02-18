//
// Created by Lyam Talbot on 5/2/2025.
//

#ifndef IM_APP_STRUCTS_H
#define IM_APP_STRUCTS_H
#include <string>
#include <vector>
#include "Poco/Net/StreamSocket.h"

struct user_struct_t {
    std::string username;
    std::string pw_hash;
    std::string salt;
    std::vector<std::string> messages;
};

struct socket_data_struct_t {
    Poco::Net::SocketAddress address;
    Poco::Net::StreamSocket* sp;
    std::mutex socket_mutex;
};

struct message_struct_t {
    std::string sender;
    std::string message;
    std::time_t timestamp;
};


#endif //IM_APP_STRUCTS_H
