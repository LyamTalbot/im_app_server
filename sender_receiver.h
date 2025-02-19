//
// Created by Lyam Talbot on 19/2/2025.
//

#ifndef SENDER_RECEIVER_H
#define SENDER_RECEIVER_H
#include <thread>
#include <queue>
#include <string>
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "im_app_structs.h"

void sender(Poco::Net::StreamSocket& socket, const std::queue<message_struct_t>& messages);

void receiver(const Poco::Net::StreamSocket& socket);

void send_message(std::string message);



#endif //SENDER_RECEIVER_H
