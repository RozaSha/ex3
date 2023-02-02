#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "KNN.h"
#include "PreProcess.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


using namespace std;

int main(int argc, char *argv[]) {
    //Check the input.
    //Checking the user sent only two arguments.
    if (argc != 3) {
        std::cerr << "Error: Too many or not enough arguments." << std::endl;
        return 1;
    }
    // making sure the second input is a positive integer and can be used for port number.
    if (!positiveInteger(argv[2])) {
        std::cerr << "Error: second argument is not a positive integer." << std::endl;
        return 1;
    }
    // saving port number.
    const int server_port = stoi(argv[2]);
    if (server_port < 1024 || server_port > 65535) {
        std::cerr << "Error: cannot use this port." << std::endl;
        return 1;
    }
    // making sure the csv file is valid.
    // making sure the address link to a valid csv file.
    std::string filePath(argv[1]);
    std::ifstream file(filePath);
    if (!file.good()) {
        std::cerr << "Error: the file '" << filePath << "' does not exist." << std::endl;
        return 1;
    }
    // Check if the file was successfully opened
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    //Process the input.
    int featureNumber;
    // Create a vector of vectors to store the values
    vector<vector<double> > values;
    vector<string> names; // vector that will contain all the names of the possible Classifications.
    // Read the file line by line
    string line;
    while (getline(file, line)) {
        // Create a new vector to store the values in the current line
        vector<double> lineValues;
        vector<string> stringVec;

        // create vector of string from vector of double.
        stringVec = split(line, ",");

        if (names.empty()) {
            featureNumber = stringVec.size() - 1;
            names.push_back(stringVec[featureNumber]); // add new name to names
            stringVec[featureNumber] = "0"; // change name to number.
        } else {
            for (size_t i = 0; i < names.size(); ++i) {
                if (names[i] == stringVec[featureNumber]) {
                    // name was found in the vector names
                    // Change the value of the last element in the line to i
                    stringVec[featureNumber] = std::to_string(i);
                    break;
                }
                if (i == names.size() - 1 and names.at(i) != stringVec[featureNumber]) {
                    names.push_back(stringVec[featureNumber]); // add new name to names
                    stringVec[featureNumber] = std::to_string((i + 1)); // change name to number.
                    break;
                }
            }
        }
        // making sure all the numbers are valid.
        if (!inputCheck(stringVec)) {
            cerr << "Error: make sure all arguments of csv file are doubles except for names " << endl;
            return 1;
        }
        // create vector of double.
        lineValues = convertStringVectortoDoubleVector(stringVec);

        // Add the vector of values to the current line to the main vector
        values.push_back(lineValues);

        // make sure the vector we added is the same length as the first vector in the file.
        if (featureNumber + 1 != static_cast<int>(lineValues.size())) {
            cerr << "Error: not all vectors in file are the same length. " << endl;
            return 1;
        }
    }
    // Close the file
    file.close();
    //Creat KNN object.
    KNN knn(values);
    //Creating socket.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("error creating socket"); }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    //Bind.
    if (::bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    //Listen
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock;
    while (true) {
        client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            perror("error accepting client");
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        while (read_bytes > 0) {
            vector<double> inputVector;
            string type;
            int k;
            string input = string(buffer);
            vector<std::string> vs1 = split(input, " ");
            vs1.erase(std::find_if(vs1.rbegin(), vs1.rend(), [](int ch) {
                return !std::isspace(ch);
            }).base(), vs1.end());
            //check if the last input is integer and assigning it to k.
            if (!positiveInteger(vs1[vs1.size() - 1])) {
                string sendMessage = "invalid input";
                int sent_bytes = send(client_sock, sendMessage.c_str(), sendMessage.size(), 0);
                if (sent_bytes < 0) {
                    perror("error sending to client");
                }
                break;
            }
            k = std::stoi(vs1[vs1.size() - 1]);
            if (k > static_cast<int>(values.size())) {
                string sendMessage = "invalid input";
                int sent_bytes = send(client_sock, sendMessage.c_str(), sendMessage.size(), 0);
                if (sent_bytes < 0) {
                    perror("error sending to client");
                }
                break;
            }
            vs1.pop_back();
            //checking if string is correct and assigning it to type.
            if (!distanceMetric(vs1[vs1.size() - 1])) {
                string sendMessage = "invalid input";
                int sent_bytes = send(client_sock, sendMessage.c_str(), sendMessage.size(), 0);
                if (sent_bytes < 0) {
                    perror("error sending to client");
                }
                break;
            }
            type = vs1[vs1.size() - 1];
            vs1.pop_back();
            //checking if string is correct and assigning it to type.
            if (vs1.size() + 1 != values[0].size()) {
                string sendMessage = "invalid input";
                int sent_bytes = send(client_sock, sendMessage.c_str(), sendMessage.size(), 0);
                if (sent_bytes < 0) {
                    perror("error sending to client");
                }
                break;
            }
            //checking the vector if it all double.
            if (!inputCheck(vs1)) {
                string sendMessage = "invalid input";
                int sent_bytes = send(client_sock, sendMessage.c_str(), sendMessage.size(), 0);
                if (sent_bytes < 0) {
                    perror("error sending to client");
                }
                break;
            }
            inputVector = convertStringVectortoDoubleVector(vs1);
            //classifying the input vector.
            int classified = knn.classify(inputVector, k, type, names.size());
            string finalClassification = names[classified];
            //returning the classification to the client.
            int sent_bytes = send(client_sock, finalClassification.c_str(), read_bytes, 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
            }
            memset(buffer, 0, sizeof(buffer));
            read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        }
        close(client_sock);
    }
}