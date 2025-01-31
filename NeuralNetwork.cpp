//TODO (new)
//1) See if num_outputs is the samne as the number of nodes in the last layer aka outpouts = last node layer
//2) Make it so that the NNparameters CSV has to be filled out correctly else itll throw some kind of error
//3) Fix the inpout NN function
//4) Make a training function which trains each training example in a dataset
//5) Go through all set and gets and make sure all are 0 based and not 1 based

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

    // Dynamically allocate memory for node_layer, z values, biases, and weights arrays
    node_layer = new Matrix[num_hidden_layers + 2];
    z = new Matrix[num_hidden_layers + 1];

    biases = new Matrix[num_hidden_layers + 1];
    weights = new Matrix[num_hidden_layers + 1];

    node_layer[0] = Matrix(num_inputs, 1); // Initialize input vector
    correct_output = Matrix(num_outputs,1);

    for (int i = 0; i < num_hidden_layers; i++) {
        node_layer[i+1] = Matrix(hidden_layer_sizes[i], 1); // Create node layer vectors
        z[i] = Matrix(hidden_layer_sizes[i], 1); //Create z layer vectors
        biases[i] = Matrix(hidden_layer_sizes[i], 1); // Create bias vectors for each node layer
    }

    node_layer[num_hidden_layers+1] = Matrix(num_outputs, 1);
    z[num_hidden_layers] = Matrix(num_outputs, 1); //Create the z vector for the output vector
    biases[num_hidden_layers] = Matrix(num_outputs, 1); // Create the bias vector for the output vector

    // Part 2: Initializing the weight matrices
    weights[0] = Matrix(hidden_layer_sizes[0], num_inputs); // First weight matrix

    for (int i = 1; i < num_hidden_layers; i++) {
        weights[i] = Matrix(hidden_layer_sizes[i], hidden_layer_sizes[i - 1]); // The middle weight matrices
    }

    weights[num_hidden_layers] = Matrix(num_outputs, hidden_layer_sizes[num_hidden_layers - 1]); // The final weight matrix

    initialize_zero();

    learning_rate = 0.001;
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
    node_layer[0].initialize_zero();
    for(int i = 0; i<num_hidden_layers+1; i++){
        node_layer[i+1].initialize_zero();
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
    try{
    for(int i = 0; i<num_hidden_layers+1; i++){
        line = "";
        getline(inputFile,line); //First set of actual data is on seventh line in the form: <number of hidden layers>, <number of outputs>
        stringstream inputString(line); //For parsing csv
        for(int j = 0; j<weights[i].rows; j++){
            for(int k = 0; k<weights[i].columns; k++){
                getline(inputString, tempString, ',');
                cout<<"HERE1\n";
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
            cout<<"HERE2\n";
            bias = stof(tempString);
            biases[i].set(j,0,bias);
        }
    }
    }catch(exception e){
        cout<<"The neural network input file is not set up properly. Fix the file and try again"<<"\n";
    }



    inputFile.close();
}


//Save the current NN parameters to a csv file (I should probably make a better format for the csv files)
void NeuralNetwork::save_to_file(){
    ofstream outputFile; //file reader object
    outputFile.open("./abc.csv"); //open file that contains Network Parameters TODO: make this adjustable
    if (outputFile.is_open()) { // Check if the file opened successfully
        //Write initial text
        outputFile << "Do NOT remove this line. Make sure to only use integers and to separate numbers using commas. Enter information on lines 3 and 5.\n";
        outputFile << "On line below: <number of inputs>, <number of hidden layers>, <number of outputs>\n";

        //Write the <number of inputs>, <number of hidden layers>, <number of outputs>
        outputFile << num_inputs<<","<<num_hidden_layers<<","<<num_outputs<<"\n";

        //Write explainer text
        outputFile << "On line below: <number of nodes in the first hidden layer>, ... <number of nodes in the nth hidden layer>\n";
        for(int i = 0; i<num_hidden_layers;i++){
            outputFile<<hidden_layer_sizes[i]<<",";
        }
        outputFile << "\n";

        //Write more explainer text
        outputFile << "On the lines below enter the values of the weights. Just enter the values in row by one so r1,r1...r2,r2,...rn,rn... for a weight matrix. Each weight matrix has one line\n";
        //Write the weight values
        for(int i = 0; i<num_hidden_layers+1; i++){
            for(int j = 0; j<weights[i].rows; j++){
                for(int k = 0; k<weights[i].columns; k++){
                    outputFile << weights[i].get(j,k)<<",";
                }
            }
            outputFile<<"\n";
        }

        //Write more explainer text
        outputFile << "On the lines below enter the bias values. Each new line is a new bias vectors\n";
        for(int i = 0; i<num_hidden_layers+1; i++){
            for(int j = 0; j<biases[i].rows; j++){
                outputFile << biases[i].get(j,0)<<",";
            }
            outputFile<<"\n";
        }
        outputFile.close(); // Close the file
    } else {
        cout << "Error opening file!\n";
        exit(1);
    }
}

//Neural Network Functions for Determining Output
int NeuralNetwork::input_NN(int numb){


    //Part 1: Input the new Value

    //z[0] = (weights[0]*node_layer[0]) + biases[0];

    //Part 2: Generate Output from the input
    for(int i = 0; i<num_hidden_layers+1; i++){
        z[i] = (weights[i]*node_layer[i]) + biases[i];
        node_layer[i+1] = ReLu(z[i]);
        //cout<<"I == "<<i<<" 00000000000000000000000000000000000000000000000000000000\n";
    }
    
    //Return the Networks Choice: the output node with the highest value
    choice = 0;
    for(int i = 1; i<num_outputs; i++){
        if(numb == 0){
            node_layer[num_hidden_layers+1].print();
        }
        if(node_layer[num_hidden_layers+1].get(i,0) > node_layer[num_hidden_layers+1].get(choice,0)){
            choice = i;
        }
    }
    if(numb == 0){
        //cout<<"Choice: "<<node_layer[num_hidden_layers].get(choice,0)<<"\n";
        cout<<"Choice: "<<choice<<"\n";
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
        node_layer[0].set(i,0,intermediate);
    }
    //cout<<"Matrix Input: "<<node_layer[0].rows<<" x "<<node_layer[0].columns<<"\n";

    input_NN(0);
}

//Train_Example
void NeuralNetwork::train(){

    input_NN(1); //fix this later
    

    Matrix del_prev;
    Matrix weights_prev;

    //2) Compute del_L
    Matrix del = clipGradients((node_layer[num_hidden_layers+1]-correct_output)%step(z[num_hidden_layers]),max_norm);

    //4) Propogate the reults back to the start
    for(int i = num_hidden_layers; i >= 0; i--){

        //4.2) Delete Old weight_matrix_intermediate and then get the new one
        weights_prev = weights[i];

        //4.3 Adjust weights: TODO: might be doing pointer arithmetic instead of matrix arithmetic
        weights[i] = weights[i] - learning_rate*(del*transpose(node_layer[i])); //The node layer behind the weight matrix has the same index as it, hence the same index here

        //4.4 Adjust biases
        biases[i] = biases[i] - learning_rate*(del);

        //4.1) Store Del and then delete old del_prev
        if(i>0){
            del = clipGradients(((transpose(weights_prev)*del)%step(z[i-1])),max_norm);
        }
    }
}

//Train_Example
void NeuralNetwork::train(Matrix input, Matrix output){

    //1) Input I/O pair
    node_layer[0] = input;
    correct_output = output;

    //2) Train
    train();
}

//Train the neural network on all the training examples in a directory
//This assumes that the first row of the csv contains input values and second row contains output values
void NeuralNetwork::train_directory(int number_of_training_examples){
    ifstream inputFile; //file reader object
    string line,tempString;

    for(int i = 0; i<number_of_training_examples; i++){
        inputFile.open("./Training_Examples/"+to_string(i)+".csv"); //open file that contains training examples
        if (!inputFile){
            cerr << "Error: unable to open input file #"<<i<<endl;
        }

        getline(inputFile,line);
        stringstream inputString(line); //For parsing csv

        //Read inputs from file
        for(int i = 0; i<num_inputs; i++){
            getline(inputString, tempString, ',');
            cout<<"HERE3\n";
            node_layer[i].set(i,0,stof(tempString));
        }

        getline(inputFile,line);
        stringstream inputString2(line);

        //Read outputs from file into output vector
        for(int i = 0; i<num_outputs; i++){
            getline(inputString2, tempString, ',');
            cout<<"HERE4\n";
            correct_output.set(i,0,stof(tempString));
        }

        inputFile.close();

        train();   
    }
}

void NeuralNetwork::train_dataset(int num_epochs, int number_of_training_examples){
    
    int types_of_data = 10;
    int file_rows = 28;
    int file_columns = 28;
    string filename;

    for (int epoch = 0; epoch < num_epochs; ++epoch) {
        learning_rate *= 0.99;
        for (int i = 0; i < number_of_training_examples; ++i) {
            // Load example i and train
            for(int j = 0; j < types_of_data; j++){
                filename = "./Training_Examples/mnist/" + to_string(j) + "/" + to_string(j) + "_" + to_string(i) + ".csv";
                Matrix standard_basis_vector = Matrix(10,1);
                standard_basis_vector.initialize_zero();
                standard_basis_vector.set(j,1,1);
                train(Matrix(file_rows, file_columns, filename), standard_basis_vector);
                this->node_layer[num_hidden_layers+1].print();
            }
        }
        cout << "Epoch " << epoch + 1 << " completed." << std::endl;
    }
}

//start by printing just the nodes
void NeuralNetwork::print(){

    int p = 7;
    int q = 3;

    string space(p,' ');
    string dash_space(q, ' ');

    print_line(p,q);
    cout<<"Neural Network\n";
    // for(int i = 0; i<num_hidden_layers+1; i++){
    //     cout<<string(7*(weights[i].columns+1),' ');
    //     if(i != num_hidden_layers){
    //         cout<<dash_space;
    //     }
    // }
    // cout<<"  \n";
    print_line(p,q);

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
    cout<<fixed<<setprecision(2);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // you can loop k higher to see more color choices
    // pick the colorattribute k you want

    //Printing out the biases
    SetConsoleTextAttribute(hConsole, 13);
    cout<<"Biases:\n";
    for(int k = 0; k<max; k++){

        cout<<space<<dash_space;

        for(int j = 0; j<num_hidden_layers+1; j++){
            for(int l = 0; l<weights[j].columns; l++){
                cout<<space;
            }
            cout<<dash_space;
            if(k<node_layer[j+1].rows){
                cout<<"{";
                if(biases[j].get(k,0)>=0){
                    cout<<" ";
                }
                cout<<biases[j].get(k,0)<<"}";
            }
            else{
                cout<<space;
            }
            cout<<dash_space;
        }
        cout<<"\n";
    }

    //Printing out the weights and nodes
    SetConsoleTextAttribute(hConsole, 15);
    for(int k = 0; k<max; k++){
        if(k<num_inputs){
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"[";
            if(node_layer[0].get(k,0)>=0){
                cout<<" ";
            }
            cout<<node_layer[0].get(k,0)<<"] - ";
            SetConsoleTextAttribute(hConsole, 15);
        }
        else{
            cout<<space<<dash_space;
        }
        for(int j = 0; j<num_hidden_layers; j++){
            if(k<node_layer[j+1].rows){
                SetConsoleTextAttribute(hConsole, 14);
                for(int l = 0; l<weights[j].columns; l++){
                    cout<<"|";
                    if(weights[j].get(k,l)>=0){
                        cout<<" ";
                    }
                    cout<<weights[j].get(k,l)<<"|";
                }
                SetConsoleTextAttribute(hConsole, 15);
                cout<<" - ";
            }
            else{
                for(int l = 0; l<weights[j].columns; l++){
                    cout<<space;
                }
                cout<<dash_space;
            }
            if(k<hidden_layer_sizes[j]){
                cout<<"[";
                if(node_layer[j+1].get(k,0)>=0){
                    cout<<" ";
                }
                cout<<node_layer[j+1].get(k,0)<<"] - ";
            }
            else{
                cout<<space<<dash_space;
            }
        }
        if(k<num_outputs){
            for(int l = 0; l<weights[num_hidden_layers].columns; l++){
                SetConsoleTextAttribute(hConsole, 14);
                cout<<"|";
                if(weights[num_hidden_layers].get(k,l)>=0){
                    cout<<" ";
                }
                cout<<weights[num_hidden_layers].get(k,l)<<"|";
                SetConsoleTextAttribute(hConsole, 15);
            }
            cout<<" - ";
            SetConsoleTextAttribute(hConsole, 10);
            cout<<"[";
            if(node_layer[num_hidden_layers+1].get(k,0)>=0){
                cout<<" ";
            }
            cout<<node_layer[num_hidden_layers+1].get(k,0)<<"]";
            SetConsoleTextAttribute(hConsole, 15);
        }
        else{
            for(int l = 0; l<weights[num_hidden_layers].columns; l++){
                cout<<space<<dash_space;
            }
            cout<<space;
        }
        cout<<"\n";
    }

    //Printing out the z values
    SetConsoleTextAttribute(hConsole, 9);
    for(int k = 0; k<max; k++){
        cout<<space<<dash_space;
        for(int j = 0; j<num_hidden_layers+1; j++){
            for(int l = 0; l<weights[j].columns; l++){
                cout<<space;
            }
            cout<<dash_space;
            if(k<node_layer[j+1].rows){
                cout<<"{";
                if(z[j].get(k,0)>=0){
                    cout<<" ";
                }
                cout<<z[j].get(k,0)<<"}";
            }
            else{
                cout<<space;
            }
            cout<<dash_space;
        }
        cout<<"\n";
    }
    cout<<"Z values^\n";
    SetConsoleTextAttribute(hConsole, 15);

    print_line(p,q);
}


void NeuralNetwork::manually_change_learning_rate(){
    try{
        do{
            cout<<"\nNew Learning Rate: ";
            cin>>learning_rate;
        }while(learning_rate<=0);
    }catch(string e){
        cout<<"ERROR: not a valid learning rate: "<<e<<"\n\n";
    } 
}

void NeuralNetwork::change_learning_rate(float rate){
    learning_rate = rate;
}

void NeuralNetwork::print_line(int p, int q){

    string unit_underline(p,'=');
    string dash_underline(q, '=');

    cout<<unit_underline<<dash_underline;
    for(int i = 0; i<num_hidden_layers+1; i++){
        for(int j = 0; j<weights[i].columns; j++){
            cout<<unit_underline;
        }
        cout<<dash_underline<<unit_underline;
        if(i != num_hidden_layers){
            cout<<dash_underline;
        }
    }
    cout<<"\n";
}

Matrix NeuralNetwork::clipGradients(const Matrix& m, float maxNorm) {
    Matrix result = m;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.columns; j++) {
            float value = m.get(i, j);
            if (value > maxNorm) value = maxNorm;
            if (value < -maxNorm) value = -maxNorm;
            result.set(i, j, value);
        }
    }
    return result;
}