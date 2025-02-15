#include <iostream>
#include <cxxabi.h>
#include "Poco/Net/DNS.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include <type_traits>
#include "im_app_structs.h"
#include "shared_mutexes.hpp"
#include "user_socket_map.hpp"

#define SIZE 4096

using namespace Poco::Net;

/*
 * We need to implement an authentication system for this.
 * Who is the user? Do they have an account?
 * Have user enter username
 * Does a user with this name exist? Ask for password and check if it's correct.
 *      Password correct? Login : Deny login and ask them to re-enter password.
 * User doesn't exist? Ask them to enter a password and create a username with this username and password.
 *
 * How am I storing the userdata?
 *  Just write a function that will store the user data as comma seperated values.
 *      username, hash, salt
 *
 *  Write another function to read the data and store it in a vector.
 *  Vector of structs.
 *      username : string
 *      password_hash : string
 *      salt : string
 *      messages : vector<string>
 *
 *
 * Other considerations
 * 1. How are we going to store the user credentials?
 *      Best solution probably to add a salt and hash them (bcrypt?) then store the hash. Store salt with no encryption.
 *      Save it in what file? (Research common solutions to this)
 * 2. This auth will need to be inside the run function inside EchoConnection because each thread will need to authenticate
 *    the user connected on the other end. Each connection is to a different user and will need a different auth.
 *    Luckily the threads isolate this from each other so that makes handling and authenticating multiple users pretty easy.
 *    Still need to think about how the EchoConnetion is going to have access to the data file and where that will be loaded in?
 *    I could load the file in directly for each auth request? Dunno.
 *
 *  3. Sending messages to other people
 *     Once basic authentication is
 *
 *
 *  4. Information encoding
 *     How am I going to send the information to the server?
 *     More to the point how will I delimit between different piece of information.
 *     If I want to send a username and password how am I going to send that and how is
 *     the server going to split it and know what is what?
 *     If I just send the piece of information on 1 line with spaces in between I can use
 *     the c++ stream operator to separate it right?
 *     "<username> <password>" -> server
 *     server receives and reads from the socket into a buffer.
 *     can I just buffer >> username >> password; ?
 */

/*
 * We will want to iterate over the hashmap of socket pointers and then write to them.
 * Can use this
 * for (auto& it: B){
 *      // Do stuff
 *      cout << it.first;
 *      }
 */

class EchoConnection : public TCPServerConnection {
public:
    explicit EchoConnection(const StreamSocket& s) : TCPServerConnection(s) {}

    bool logged_in = false;
    void run() override {
        user_struct user;
        StreamSocket& ss = socket();
        //TODO add a mutex for this
        map_mutex.lock();
        port_socket_map[ss.peerAddress().port()] = &ss;
        map_mutex.unlock();
        ss.setBlocking(true);
        // if (!logged_in) {
        //     char buffer[SIZE];
        //     std::string message = "Please enter a username and password";
        //     ss.sendBytes(message.c_str(), message.size());
            //TODO get username and password - did I decide on how that information will be encoded?
            //we can get the port number from ss.peerAddress();
            //will return the IP and port number of the port on the other side.
            //Instead of fucking around with user auth I'll just try to implement the ability to broadcast
            //to all connected clients before I go any further.
            //Once that's done I'll implement logins
            //Then after we have that set up I'll try to direct a message to a particular user.
            // n = ss.receiveBytes(buffer, sizeof(buffer));
            // std::string username = buffer;
            // user_socket_map[username] = &ss;
            //TODO split username off -> add them to the hashmap with a reference to the socket

            //TODO integrate user_authentication
            //Will need users set up first
            //First create a text file with the formatting for saving users
            //Then we can try to create a list of users and see if that works
            //If that works we can try to login with the python script on
            //I guess this is why unit tests are good, testing things in isolation before
            //trying to integrate the code.
        // }
        try {
            char buffer[SIZE];
            int n = ss.receiveBytes(buffer, sizeof(buffer));
            while (n > 0) {
                ss.sendBytes(buffer, n);
                n = ss.receiveBytes(buffer, sizeof(buffer));
            }
        } catch (Poco::Exception& e) {
            std::cerr << "EchoConnection: " << e.displayText() << std::endl;
        }

    }
};

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    TCPServer srv(new TCPServerConnectionFactoryImpl<EchoConnection>());
    srv.start();
    std::cout << srv.socket().address().port() << std::endl;
    // SocketAddress sa("localhost", srv.socket().address().port());
    // StreamSocket ss(sa);
    // std::cout << "Please enter a message" << std::endl;
    // std::string data;
    // getline(std::cin, data);
    // while ((strcmp(data.data(), "\0")) != 0) {
    //     ss.sendBytes(data.data(), static_cast<int>(data.size()));
    //     char buffer[256] = {0};
    //     int n = ss.receiveBytes(buffer, sizeof(buffer));
    //     std::cout << std::string(buffer, n) << std::endl;
    //     std::cout << "Please enter a message" << std::endl;
    //     getline(std::cin, data);
    // }
    while (true) {
        Poco::Thread::sleep(1000);  // Sleep to avoid high CPU usage
    }
    srv.stop();
}
