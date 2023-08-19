#include<iostream>
#include<fstream>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

    fstream file;

    int PORT;
    
    int general_socket_descriptor;
    int new_socket_descriptor;

    struct sockaddr_in address;
    int address_length;

void transmit_file(){
            std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            cout<<"[ [+] UPDATE] -- The Size of the file to send -- "<<contents.length()<<" Bytes.\n";
            cout<<"[ [+] UPDATE] -- File is being transmitted, please wait ..." << endl;

            int bytes_sent = send(new_socket_descriptor , contents.c_str() , contents.length() , 0 );
            cout<<"[ [+] UPDATE] -- Transmitted Data Size "<<bytes_sent<<" Bytes.\n";

            cout<<"[ [+] UPDATE] -- File has successfully been transmitted." << endl;
        }


int main(){
    
                //creating the socket 
            if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
                perror("[ [-] ERROR] -- Socket has failed to be established");
                exit(EXIT_FAILURE);
            }
            cout<<"[ [+] UPDATE] -- Socket Created Successfully.\n";
        
            PORT = 8031;

            address.sin_family = AF_INET; 
            address.sin_addr.s_addr = INADDR_ANY; 
            address.sin_port = htons( PORT );
            address_length = sizeof(address);

            //binding socket 

            if (bind(general_socket_descriptor, (struct sockaddr *)&address, sizeof(address))<0) {
                perror("[[-] ERROR] -- socket Bind failed");
                exit(EXIT_FAILURE);
            }

            cout<<"[ [+] UPDATE] -- socket Binding was Successful." << endl;
             if (listen(general_socket_descriptor, 3) < 0) {
                perror("[ [-] ERROR] -- Listening");
                exit(EXIT_FAILURE);
            }

            //waiting for connection 
            cout<<"[ [+] UPDATE] -- Socket in Listening State " << endl;

            //accept connect
             if ((new_socket_descriptor = accept(general_socket_descriptor, (struct sockaddr *)&address, (socklen_t*)&address_length))<0) { 
                perror("[ [-] ERROR] -- Accepting");
                exit(EXIT_FAILURE);
            }
            cout<<"[ [+] UPDATE] -- Connected to Client." << endl;

            file.open("send.txt", ios::in | ios::binary);
            if(file.is_open()){
                cout<<"[ [+] UPDATE] -- File is ready to be sent." <<endl;
            }
            else{
                cout<<"[ [-] ERROR] -- failed to access file. Exititng." << endl;
                exit(EXIT_FAILURE);
            }

            transmit_file();
        }

        
