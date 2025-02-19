# README

This readme will serve as a journal of my experiences developing this program, my thought processes and my struggles.
I have never attempted a project of this complexity, already I've had to develop new skills and an understanding of CMake as a build system
of CLION as an IDE, how to integrate packages into a C++ project. Working with libraries I've never used before, namely the Poco library and it's networking
components and TCPServer class. 

This program is not intended to be used in any real capacity, it is a project I am working on out of my own interest and as a method of developing my skills
as a programmer and a developer. This program will have a lot of edges, but I will do my best to ensure that it is designed in a thoughtful and coherent way.

More Readme stuff to follow. You know when there's more here. 

Additionally - This repo contains only the code for the c++ backend, right now the "front-end" is a simple python program. I may continue to develop the front-end
in python with a GUI or I may pivot and develop it in another language, I'll most likely stick with Python though because the client does not need to do very much. 


## 19 FEB
This is becoming a journal, using this to try and organise my thoughts because I realised I've fallen into that spiral 
of coding without really planning how parts are going to work together, I want to stop that and avoid backing myself into 
a corner.

I want to have 2 sockets, one for inbound traffic and one for outbound traffic.
This removes synchronisation issues and should make sending and receiving in real time a bit easier to manage.
Each socket will be serviced by its own thread. One issue I'm not sure how to address is how I want to queue the messages
for a particular outbound socket? Where should that queue be stored and how do I get a reference to it from inside the 
thread entry point? I want to associate a queue of messages with a particular person but where do I store that
How is it organised? Maybe in my port socket map. There's a queue of messages in the socket data map.
This may not be secure, there's a temptation to encapsulate this stuff in a class for more security but how necessary is that really?
Especially in this circumstance where I just want to build the thing, it's not going to be used.

### Message Encoding

#### Receiving
How do we want to send the messages?
I want a message to contain the sender's username, the message content, ~~time stamp~~.
If I separate using spaces that's pretty easy because I can use the c++ stream operator to pull information out of the string
I can get a line from the socket? ending at....not new line because the message string might contain newlines. Maybe a null terminator? \0.
Looks like SocketInputStream from the Poco library will help with this. 
Reads information into a std::istream like object
    Poco::Net::SocketInputStream iss;
    Char[SIZE] buffer; 
    getline(iss, buffer, '\0');
This will read until we get hit a null terminator and put it into buffer. 
As long as I define buffer to be large enough to handle our max message size we can't buffer overrun. Great?

#### Sending
Sending is probably a little easier.
Take the string that the user has entered, concatenate it with their username and null terminate it. 
Send that over a socket.
