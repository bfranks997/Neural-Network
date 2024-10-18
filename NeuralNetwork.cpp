//~let N be the number of layers in our Neural Netowrk
//We need some objects:
//  1) Nodes: These are simply vectors. You need One input vector, one output vector, and then another N vectors (one for each layer)
//  2) Weight Matrices: Matrices, you need N+1 weight matrices (N, one for each layer + 1 for output)

//TODO (old):
// = assignment operator
//fix the stupid pointer stuff with the matrices. No reason to return a pointer. Just use the pointer to edit
//make a node reset function

//TODO (new)
//1) Verify algorithm is correct
//2) Create random initialization for neural network
//3) Verify the nounds in for loops are correct
//4) Figure out if the dynamic allocation of memory is correct
//5) Do a simple train and test with the simplest network possible
//6) LEARN TO DEBUG SO YOU CAN FIX THE HIDDEN LAYER SIZES CHANGING
//7) See if num_outputs is the samne as the number of nodes in the last layer aka outpouts = last node layer
//8) Make it so that the NNparameters CSV has to be filled out correctly else itll throw some kind of error
//9) Fix the inpout NN function

#include "NeuralNetwork.h"
#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>

using namespace std;

NeuralNetwork::NeuralNetwork()
{

    ifstream inputFile; //file reader object
    inputFile.open("./NeuralNetworkParameters.csv"); //open file that contains Network Parameters TODO: make this adjustable

    string line = "";

    string tempString;

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

    hidden_layer_sizes = new int[num_hidden_layers];

    for(int i = 0; i<num_hidden_layers; i++){
        getline(inputString2, tempString, ','); //get a hidden layer size
        hidden_layer_sizes[i] = stoi(tempString);
    }

    hidden_layer_sizes[num_hidden_layers] = num_outputs;

    // Close file
    inputFile.close();

    //-------------------------------------------------------------
    // Part 1: Initializing Inputs, outputs, weights, and biases
    inputs = Matrix(num_inputs, 1); // Initialize input vector

    // Dynamically allocate memory for node_layer, z values, biases, and weights arrays
    node_layer = new Matrix[num_hidden_layers + 1];
    z = new Matrix[num_hidden_layers + 1];

    biases = new Matrix[num_hidden_layers + 1];
    weights = new Matrix[num_hidden_layers + 1];

    for (int i = 0; i < num_hidden_layers; i++) {
        node_layer[i] = Matrix(hidden_layer_sizes[i], 1); // Create node layer vectors
        z[i] = Matrix(hidden_layer_sizes[i], 1); //Create z layer vectors
        biases[i] = Matrix(hidden_layer_sizes[i], 1); // Create bias vectors for each node layer
    }

    node_layer[num_hidden_layers] = Matrix(num_outputs, 1);
    z[num_hidden_layers] = Matrix(num_outputs, 1); //Create the z vector for the output vector
    biases[num_hidden_layers] = Matrix(num_outputs, 1); // Create the bias vector for the output vector

    // Part 2: Initializing the weight matrices

    weights[0] = Matrix(hidden_layer_sizes[0], num_inputs); // First weight matrix

    for (int i = 1; i < num_hidden_layers; i++) {
        weights[i] = Matrix(hidden_layer_sizes[i], hidden_layer_sizes[i - 1]); // The middle weight matrices
    }

    weights[num_hidden_layers] = Matrix(num_outputs, hidden_layer_sizes[num_hidden_layers - 1]); // The final weight matrix

    initialize_zero();
}


NeuralNetwork::~NeuralNetwork() {
    delete[] hidden_layer_sizes;
    delete[] node_layer; // Use delete[] for dynamically allocated arrays
    delete[] z;
    delete[] weights;    // Use delete[] for dynamically allocated arrays
    delete[] biases;     // Use delete[] for dynamically allocated arrays
}

void NeuralNetwork::initialize_values_random(){
    for (int i = 0; i < num_hidden_layers+1; i++) {
        weights[i].initialize_random();
        biases[i].initialize_random();
    }
}

void NeuralNetwork::initialize_zero(){
    inputs.initialize_zero();
    for(int i = 0; i<num_hidden_layers+1; i++){
        node_layer[i].initialize_zero();
        weights[i].initialize_zero();
        biases[i].initialize_zero();
        z[i].initialize_zero();
    }
}

void NeuralNetwork::initialize_from_file(){
    ifstream inputFile; //file reader object
    inputFile.open("./NeuralNetworkParameters.csv"); //open file that contains Network Parameters TODO: make this adjustable
    string line = "";
    string tempString;
    getline(inputFile,line); //ignore first line
    getline(inputFile,line); //ignore second line
    getline(inputFile,line); //ignore third line
    getline(inputFile,line); //ignore fourth line
    getline(inputFile,line); //ignore fifth line
    getline(inputFile,line); //ignore sixth line

    float weight = 0;
    //Parse the lines (1 line per hidden layer +1)
    for(int i = 0; i<num_hidden_layers+1; i++){
        line = "";
        getline(inputFile,line); //First set of actual data is on seventh line in the form: <number of hidden layers>, <number of outputs>
        stringstream inputString(line); //For parsing csv
        for(int j = 0; j<weights[i].rows; j++){
            for(int k = 0; k<weights[i].columns; k++){
                getline(inputString, tempString, ',');
                weight = stof(tempString);
                weights[i].set(j,k,weight);
            }
        }
    }

    float bias = 0;

    getline(inputFile,line); //bias explainer line
    for(int i = 0; i<num_hidden_layers+1; i++){
        line = "";
        getline(inputFile,line); //First set of actual data is on seventh line in the form: <number of hidden layers>, <number of outputs>
        stringstream inputString(line); //For parsing csv
        for(int j = 0; j<biases[i].rows; j++){
            getline(inputString, tempString, ',');
            bias = stof(tempString);
            cout<<"SETTING BIAS TO: "<<bias<<", current value is "<<biases[i].get(j,1)<<"\n";
            biases[i].set(j,0,bias);
            cout<<"BIAS SET TO: "<<biases[i].get(j,1)<<"\n";
        }
    }


    inputFile.close();
}

void NeuralNetwork::save_to_file(){
    ofstream outputFile; //file reader object
    outputFile.open("./NeuralNetworkParameters.csv"); //open file that contains Network Parameters TODO: make this adjustable
    string line = "";
    string tempString;
    getline(inputFile,line); //ignore first line
    getline(inputFile,line); //ignore second line
    getline(inputFile,line); //ignore third line
    getline(inputFile,line); //ignore fourth line
    getline(inputFile,line); //ignore fifth line
    getline(inputFile,line); //ignore sixth line

    float weight = 0;
    //Parse the lines (1 line per hidden layer +1)
    for(int i = 0; i<num_hidden_layers+1; i++){
        line = "";
        getline(inputFile,line); //First set of actual data is on seventh line in the form: <number of hidden layers>, <number of outputs>
        stringstream inputString(line); //For parsing csv
        for(int j = 0; j<weights[i].rows; j++){
            for(int k = 0; k<weights[i].columns; k++){
                getline(inputString, tempString, ',');
                weight = stof(tempString);
                weights[i].set(j,k,weight);
            }
        }
    }

    float bias = 0;

    getline(inputFile,line); //bias explainer line
    for(int i = 0; i<num_hidden_layers+1; i++){
        line = "";
        getline(inputFile,line); //First set of actual data is on seventh line in the form: <number of hidden layers>, <number of outputs>
        stringstream inputString(line); //For parsing csv
        for(int j = 0; j<biases[i].rows; j++){
            getline(inputString, tempString, ',');
            bias = stof(tempString);
            cout<<"SETTING BIAS TO: "<<bias<<", current value is "<<biases[i].get(j,1)<<"\n";
            biases[i].set(j,0,bias);
            cout<<"BIAS SET TO: "<<biases[i].get(j,1)<<"\n";
        }
    }


    inputFile.close();
}

//Neural Network Functions for Determining Output
int NeuralNetwork::input_NN(){


    //Part 1: Reset the Node Values and Input the new Value
    inputs.print();
    z[0] = (weights[0]*inputs) - biases[0];
    node_layer[0] = ReLu(z[0]);
    inputs.print();
    //Part 2: Generate Output from the input
    for(int i = 1; i<num_hidden_layers+1; i++){
        //Next Node layer = ReLu(weight_matrix[i]*node_layer[i-1]-bias[i]);
        //(node_layer[i]) = ReLu((((this->weights)[i-1]*(this->node_layer)[i-1]) - (this->biases)[i])); //for fast compute when already trained
        z[i] = (weights[i]*node_layer[i-1]) - biases[i];
        node_layer[i] = ReLu(z[i]);
    }
    
    //Return the Networks Choice: the output node with the highest value
    choice = 0;
    for(int i = 0; i<num_outputs; i++){
        if(node_layer[num_hidden_layers].get(i,1) > node_layer[num_hidden_layers].get(choice,1)){
            choice = i;
        }
    }

    return choice;
}

void NeuralNetwork::manual_input_NN(){
    //Have the user input the manual input vector
    float intermediate;
    cout<<"Enter the values of the input vector: \n";
    for(int i = 0; i<num_inputs; i++){
        cout<<i<<","<<1<<": ";
        cin>>intermediate;
        cout<<"Intermediate = "<<intermediate<<"\n";
        inputs.set(i,0,intermediate);
    }
    std::cout<<"Matrix Input: "<<inputs.rows<<" x "<<inputs.columns<<"\n";

    input_NN();
}


//Train_Example
void NeuralNetwork::train(Matrix input, Matrix output){

    //1) Input I/O pair
    input_NN(); //fix this later

    //2) Compute del_L
    del_prev = new Matrix(num_outputs,1);
    *del_prev = (node_layer[num_hidden_layers]-output)%step(z[num_hidden_layers]);

    //3)Use del_L to calculate the changes for the output layer weights and biases
    //3.1) Store weight matrix in intermediate variable so that when you change the weight layer you can still use the weights for the next value
    weight_matrix_intermediate = new Matrix(weights[num_hidden_layers].rows,weights[num_hidden_layers].columns);
    *weight_matrix_intermediate = weights[num_hidden_layers];
    //3.2) Adjust weights in final layer
    weights[num_hidden_layers] = weights[num_hidden_layers] - learning_rate*(*del_prev*node_layer[num_hidden_layers - 1]);
    //3.3) Adjust biases of the final layer
    biases[num_hidden_layers] = biases[num_hidden_layers] - learning_rate*(*del_prev);


    //4) Propogate the reults back to the start
    for(int i = num_hidden_layers-1; i > 0; i--){

        //4.0 Initialize del vector
        del =  new Matrix(node_layer[i].rows,1);

        //4.1) Store Del and then delete old del_prev
        *del = (transpose(*del_prev)*(*weight_matrix_intermediate))%step(z[i]);
        delete del_prev;

        //4.2) Delete Old weight_matrix_intermediate and then get the new one
        delete weight_matrix_intermediate;
        weight_matrix_intermediate = new Matrix(weights[i].rows,weights[i].columns);
        *weight_matrix_intermediate = weights[i];

        //4.3 Adjust weights: TODO: might be doing pointer arithmetic instead of matrix arithmetic
        weights[i] = weights[i] - learning_rate*(*del*transpose(node_layer[i-1]));

        //4.4 Adjust biases
        biases[i] = biases[i] - learning_rate*(*del);

        //4.5 Reset the del_prev and del values
        del_prev = new Matrix(node_layer[i].rows,1);
        del_prev = del;
        delete del;

    }

    delete weight_matrix_intermediate;
    delete del_prev;
}

//start by printing just the nodes
void NeuralNetwork::print(){

    //1) Get the max number of rows so you know how long to print for
    int max = num_outputs;
    if(num_inputs>num_outputs){
        max = num_inputs;
    }
    for(int i = 0; i<num_hidden_layers+1; i++){
        if(hidden_layer_sizes[i]>max){
            max = hidden_layer_sizes[i];
        }
    }

    //0 = Black 8 = Gray
    //1 = Blue 9 = Light Blue
    //2 = Green a = Light Green
    //3 = Aqua b = Light Aqua
    //4 = Red c = Light Red
    //5 = Purple d = Light Purple
    //6 = Yellow e = Light Yellow
    //7 = White f = Bright White
    cout<<fixed<<setprecision(1);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // you can loop k higher to see more color choices
    // pick the colorattribute k you want

    //Printing out the biases
    SetConsoleTextAttribute(hConsole, 13);
    cout<<"Biases:\n";
    for(int k = 0; k<max; k++){
        cout<<"        ";

        for(int j = 0; j<num_hidden_layers+1; j++){
            for(int l = 0; l<weights[j].columns; l++){
                cout<<"     ";
                //cout<<"wwwww";
            }
            cout<<"   ";
            if(k<node_layer[j].rows){
                cout<<"{"<<biases[j].get(k,0)<<"}";
            }
            else{
                cout<<"     ";
            }
            cout<<"   ";
        }
        cout<<"\n";
    }
    

    //Printing out the weights and nodes
    SetConsoleTextAttribute(hConsole, 15);
    for(int k = 0; k<max; k++){
        if(k<num_inputs){
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"["<<inputs.get(k,0)<<"] - ";
            SetConsoleTextAttribute(hConsole, 15);
        }
        else{
            cout<<"        ";
            //cout<<"oooooooo";
            //cout<<"[0.0] - ";
        }
        for(int j = 0; j<num_hidden_layers; j++){
            if(k<node_layer[j].rows){
                SetConsoleTextAttribute(hConsole, 14);
                for(int l = 0; l<weights[j].columns; l++){
                    cout<<"|"<<weights[j].get(k,l)<<"|";
                }
                SetConsoleTextAttribute(hConsole, 15);
                cout<<" - ";
            }
            else{
                for(int l = 0; l<weights[j].columns; l++){
                    cout<<"     ";
                    //cout<<"wwwww";
                }
                cout<<"   ";
                //cout<<"zzz";
            }
            if(k<hidden_layer_sizes[j]){
                cout<<"["<<node_layer[j].get(k,0)<<"] - ";
            }
            else{
                cout<<"        ";
                //cout<<"xxxxxxxxxx";
            }
        }
        if(k<num_outputs){
            for(int l = 0; l<weights[num_hidden_layers].columns; l++){
                SetConsoleTextAttribute(hConsole, 14);
                cout<<"|"<<weights[num_hidden_layers].get(k,l)<<"|";
                SetConsoleTextAttribute(hConsole, 15);
            }
            cout<<" - ";
            SetConsoleTextAttribute(hConsole, 10);
            cout<<"["<<node_layer[num_hidden_layers].get(k,0)<<"]";
            SetConsoleTextAttribute(hConsole, 15);
        }
        else{
            for(int l = 0; l<weights[num_hidden_layers].columns; l++){
                cout<<"        ";
                //cout<<"ppppp";
            }
            cout<<"   ";
            //cout<<"bbb";
            cout<<"  ";
            //cout<<"mmmm";
        }
        cout<<"\n";
    }

    //Printing out the z values
    SetConsoleTextAttribute(hConsole, 9);
    for(int k = 0; k<max; k++){
        cout<<"        ";
        for(int j = 0; j<num_hidden_layers+1; j++){
            for(int l = 0; l<weights[j].columns; l++){
                cout<<"     ";
                //cout<<"wwwww";
            }
            cout<<"   ";
            if(k<node_layer[j].rows){
                cout<<"{"<<z[j].get(k,0)<<"}";
            }
            else{
                cout<<"     ";
            }
            cout<<"   ";
        }
        cout<<"\n";
    }
    cout<<"Z values^\n";
    SetConsoleTextAttribute(hConsole, 15);
}

