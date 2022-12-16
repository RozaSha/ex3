//
// Created by Roza Shatz 318721370 and nof golan 311430995.
//

using namespace std;
#include <iostream>
#include <string>
#include <experimental/filesystem>

#include "input_tests.h"
#include "Distances.h"

int main(int argc, char* argv[]){

    int k;

    //making sure the arguments that were received from the command line are correct for the code.
    // making sure 3 argument were received argument 1 is the make of the program it does not count.
    if (argc != 4) {
        std::cerr << "Error: not 3 arguments. Please 3 arguments to the program." << std::endl;
        return 1;
    }

    // making sure the first number is a positive integer and can be used as k in knn.
    if(!positiveInteger(argv[1])){
        std::cerr << "Error: first argument is not a positive integer." << std::endl;
        return 1;
    }
    k = stoi(argv[1]);

    // making sure the csv file is valid.
    // making sure the address link to a valid csv file.
    std::experimental::filesystem::path current_path = std::experimental::filesystem::current_path();
    std::experimental::filesystem::path file_path = current_path / argv[2];
    if (!std::experimental::filesystem::exists(file_path) and !std::experimental::filesystem::exists(argv[2])){
        std::cerr << "Error: the given classified file does not exist" << std::endl;
        return 1;
    }

    // making sure all vectors in file the same length and all numbers are valid to use.
    // TODO go over the entire file make sure it is good and put it in a form it is needed.

    // make sure the distance measurement is one of AUC, MAN, CHB, CAN, MIN.
    if(!distanceMetric(argv[3])){
        std::cerr << "Error: distance metric given does not exist in this program" << std::endl;
        return 1;
    }



    return 0;
}
