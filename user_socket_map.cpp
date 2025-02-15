//
// Created by Lyam Talbot on 15/2/2025.
//
#include "user_socket_map.hpp"


std::unordered_map<std::string, Poco::Net::StreamSocket*> user_socket_map;

std::unordered_map<int, Poco::Net::StreamSocket*> port_socket_map;

