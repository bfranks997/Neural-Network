#include "interface.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

NeuralNetwork* getNeuralNetworkParameters(){

    ifstream inputFile; //file reader object
    inputFile.open("./NeuralNetworkParameters.csv"); //open file that contains Network Parameters TODO: make this adjustable

    string line = "";

    string tempString;
    int num_inputs, num_hidden_layers, num_outputs;

    getline(inputFile,line); //ignore first line
    getline(inputFile,line); //ignore second line
    //Parsing 3rd Line
    getline(inputFile,line); //First set of actual data is on second line in the form: <number of hidden layers>, <number of outputs>

    stringstream inputString(line); //For parsing csv

    getline(inputString, tempString, ','); //get number of inputs
    num_inputs = stoi(tempString);
    getline(inputString, tempString, ','); //get number of hidden layers
    num_hidden_layers = stoi(tempString);
    getline(inputString, tempString, ','); //get number of inputs
    num_outputs = stoi(tempString);

    getline(inputFile,line); //ignore 4th Line

    

    //Parsing 5th line and putting all the I/O quantities in their respective array slots
    line = "";
    getline(inputFile,line);
    stringstream inputString2(line);

    int * hidden_layer_sizes = new int[num_hidden_layers];

    for(int i = 0; i<num_hidden_layers; i++){
        getline(inputString2, tempString, ','); //get a hidden layer size
        hidden_layer_sizes[i] = stoi(tempString);
    }

    // Construct NeuralNetwork object
    NeuralNetwork* nn = new NeuralNetwork(num_inputs, num_hidden_layers, num_outputs, hidden_layer_sizes);

    // Clean up dynamic memory
    delete[] hidden_layer_sizes;

    // Close file
    inputFile.close();

    // Return pointer to NeuralNetwork object
    return nn;
}