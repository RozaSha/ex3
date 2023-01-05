#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
#include <algorithm>  // for std::find
#include "PreProcess.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Check for the correct number of command line arguments
    if (argc != 3) {
        //std::cerr << "Usage: " << argv[0] << " <IP address> <port>" << std::endl;
        return 1;
    }

    // Read the IP address and port number from the command line arguments
    std::string ip_address = argv[1];
    int port = std::stoi(argv[2]);

    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { // if socket was not created exit the program.
        return 1;
    }

    // Connect to the server
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip_address.c_str());
    // connect to server results.
    int result = connect(sockfd, (sockaddr *) &serv_addr, sizeof(serv_addr));
    // if it could not connect exit program.
    if (result < 0) {

        return 1;
    }

    // if it could connect to server.
    // Read input from the user and send it to the server
    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "-1") {
            // Close the connection to the server
            close(sockfd);
            break;
        }

        // split strings to vec at " ".
        vector<std::string> vs1 = split(input, " ");

        // check the values we got from the user.
        // making sure the last number is a positive integer and can be used as k in knn.
        if (!positiveInteger(vs1[vs1.size() - 1])) {
            cout << "invalid input";
            continue;
        }

        // make sure the distance measurement is one of AUC, MAN, CHB, CAN, MIN.
        if (!distanceMetric(vs1[vs1.size() - 2])) {
            cout << "invalid input";
            continue;
        }

        vs1.pop_back();
        vs1.pop_back();
        // making sure all the given values are doubles.
        if (!inputCheck(vs1)) {
            cout << "invalid input";
            continue;
        }

        // Send the message to the server
        char buf[4096];
        int bytes_sent = send(sockfd, input.c_str(), input.length(), 0);
        if (bytes_sent < 0) {
            // could not send to server
            continue;
        }
        memset(buf, 0, 4096);
        int bytes_receive = recv(sockfd, buf, 4096, 0);
        cout << string(buf, bytes_receive) << endl;
    }
    return 0;
}


