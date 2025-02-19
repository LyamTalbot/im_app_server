//
// Created by Lyam Talbot on 19/2/2025.
//

#include "sender_receiver.h"
#include "user_socket_map.hpp"

#define MAX_MESSAGES 8192

void sender(Poco::Net::StreamSocket& socket, std::queue<message_struct_t>& messages) {
    if (!messages.empty()) {
        message_struct_t message = messages.front();
        messages.pop();
        //TODO Decide how to send the messages
        //How is the information encoded?
        //This is probably the next thing to really work out.
    }
}

void receiver(const Poco::Net::StreamSocket& socket) {
    Poco::Net::SocketInputStream iss(socket);
    std::string buffer;
    std::string username;
    std::string message;
    while (true) {
        message_struct_t user_message;
        std::getline(iss, buffer, '\0');
        username = buffer.substr(0, buffer.find(' '));
        message = buffer.substr(buffer.find(' ') + 1, buffer.size());
        user_message.sender = username;
        user_message.message = message;
        socket_data_struct_t* user_data = user_data_map[username];
        user_data->message_queue.push(std::move(user_message));
    }
}