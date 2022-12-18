//
// Created by Roza Shatz 318721370 and nof golan 311430995.
//

using namespace std;
#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>  // for std::find

#include "PreProcess.h"
#include "KNN.h"



int main(int argc, char* argv[]){
    int k;
    int featureNumber;

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

    // savin k.
    k = stoi(argv[1]);

    // making sure the csv file is valid.
    // making sure the address link to a valid csv file.
    std::experimental::filesystem::path current_path = std::experimental::filesystem::current_path();
    std::experimental::filesystem::path file_path = current_path / argv[2];
    if (!std::experimental::filesystem::exists(file_path) and !std::experimental::filesystem::exists(argv[2])){
        std::cerr << "Error: the given classified file does not exist" << std::endl;
        return 1;
    }

    // open csv file.
    ifstream file(argv[2]);

    // Check if the file was successfully opened
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    // Create a vector of vectors to store the values
    vector<vector<double>> values;
    vector<string> names; // vector that will contain all the names of the inputs.

    // Read the file line by line
    string line;


    while (getline(file, line)) {
        // Create a new vector to store the values in the current line
        vector<double> lineValues;
        vector<string> stringVec;

        // create vector of string from vector of double.
        stringVec = split(line, ",");

        if(names.empty()){
            featureNumber = stringVec.size()-1;
            names.push_back(stringVec[featureNumber]); // add new name to names
            stringVec[featureNumber] = "0"; // change name to number.
        }
        else {
            for (int i = 0; i < names.size(); ++i) {
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
        if(!inputCheck(stringVec)){
            cerr << "Error: make sure all arguments of csv file are doubles except for names " << endl;
            return 1;
        }

        // create vector of double.
        lineValues = convertStringVectortoDoubleVector(stringVec);

        // Add the vector of values to the current line to the main vector
        values.push_back(lineValues);

        // make sure the vector we added is the same length as the first vector in the file.
        if(featureNumber+1 != lineValues.size()){
            cerr << "Error: not all vectors in file are the same length. " << endl;
            return 1;
        }
    }
    // Close the file
    file.close();

    // make sure the distance measurement is one of AUC, MAN, CHB, CAN, MIN.
    if(!distanceMetric(argv[3])){
        std::cerr << "Error: distance metric given does not exist in this program" << std::endl;
        return 1;
    }


    // create knn object.
    // TODO
    knni =  KNN(k, distanceMetric, values, names.size());

    //get vector to calculate knn nonstop.
    while(true){

        //get vector from user.
        string s;
        getline(cin, s);

        // split strings to vec at " ".
        vector <string> vs1 = split(s, " ");
        // check if vectors have valid numbers for calculations.
        // add decimal point if needed.
        if(!inputCheck(vs1)){
            std::cerr << "Error: values given are not doubles." << std::endl;
            return 1;
        }
        if(vs1.size() != featureNumber){
            std::cerr << "Error: vector length is not correct." << std::endl;
            return 1;
        }

        v = convertStringVectortoDoubleVector(vs1);

        // TODO
        // run knn and print result.
        cout << classify(v);

    }

    return 0;
}
