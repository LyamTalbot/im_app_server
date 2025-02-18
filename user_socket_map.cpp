//
// Created by Lyam Talbot on 15/2/2025.
//
#include "user_socket_map.hpp"
#include "im_app_structs.h"


std::unordered_map<std::string, Poco::Net::StreamSocket*> user_socket_map;

std::unordered_map<int, Poco::Net::StreamSocket*> port_socket_map;

std::unordered_map<int, socket_data_struct_t*> socket_data_map;