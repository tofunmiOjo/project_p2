#include<iostream>
#include<fstream>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include "rc4Good.h"
#include <vector>

using namespace std;


bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int get_e(int phi_n) {
    int e = phi_n - 1; // start with the largest possible value of e
    while (e > 1) {
        if (gcd(e, phi_n) == 1) {
            return e;
        }
        e--;
    }
    return -1; // no suitable value of e found
}


vector<int> find_primes(int start, int end) {
    vector<int> primes;
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) primes.push_back(i);
    }
    return primes;
}

int get_n(int p, int q){
  int n = p*q;
  return n;
}

int main(){


    fstream file;

    int PORT;

    int socketDescriptor;

    struct sockaddr_in address;
    int addr_size;


           if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                perror("[ERROR] -- Socket failed.\n");
                exit(EXIT_FAILURE);
            }
            cout<<"[UPDATE] --  Socket has Successfully been created." << endl;

            PORT = 8031;

            address.sin_family = AF_INET;
            address.sin_port = htons( PORT );
            addr_size = sizeof(address);
            if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)<=0) {
                cout<<"[ERROR] : Invalid address\n";
            }

            if (connect(socketDescriptor, (struct sockaddr *)&address, sizeof(address)) < 0) {
                perror("[ERROR] : connection attempt failed.\n");
                exit(EXIT_FAILURE);
            }
            cout<<"[UPDATE] --  Connection Successfull.\n";

            file.open("Recieved.txt", ios::out | ios::trunc | ios::binary);
            if(file.is_open()){
                cout<<"[UPDATE] --  File Creted.\n";
            }
            else{
                cout<<"[ERROR] -- Problem in accessing file ." << endl;
                exit(EXIT_FAILURE);
            }

            char buffer[10000]= {};



            int valread = read(socketDescriptor , buffer, 10000);

            cout<<"[UPDATE] --  Encyypted Data received "<<valread<<" bytes" << endl;

           

            
               
         







            cout<<"[UPDATE] --  Saving Encrypted data to file.\n";

            file<<buffer;
            cout<<"[UPDATE] --  File Saved.\n";

            return 0;


        }
