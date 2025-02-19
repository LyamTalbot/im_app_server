//
// Created by Lyam Talbot on 15/2/2025.
//

#ifndef USER_SOCKET_MAP_H
#define USER_SOCKET_MAP_H
#include "Poco/Net/StreamSocket.h"
#include "im_app_structs.h"

extern std::unordered_map<std::string, Poco::Net::StreamSocket*> user_socket_map;

extern std::unordered_map<int, Poco::Net::StreamSocket*> port_socket_map;

extern std::unordered_map<int, socket_data_struct_t*> socket_data_map;

extern std::unordered_map<int, socket_data_struct_t*> port_data_map;

extern std::unordered_map<std::string, socket_data_struct_t*> user_data_map;

#endif //USER_SOCKET_MAP_H
