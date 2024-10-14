#include <iostream>
#include "Matrix.h"
#include "NeuralNetwork.h"

using namespace std;


int main(){
    cout<<"--------------------------------------------------------------\n";
    cout<<"Welcome to the Neural Network Program by Bradley Franks V0.0.2\n";
    cout<<"--------------------------------------------------------------\n";

    NeuralNetwork myNN;
    cout<<"Inputs: "<<myNN.num_inputs<<endl;
    cout<<"Outputs: "<<myNN.num_outputs<<endl;
    cout<<"Number of Hidden Layers: "<<myNN.num_hidden_layers<<endl;
    for(int i = 0; i<myNN.num_hidden_layers; i++){
        cout<<"Size of layer "<<i<<": "<<myNN.node_layer[i].rows<<" x " <<myNN.node_layer[i].columns<<endl;
    }

    //myNN.initialize_values_random();
    // myNN.initialize_values_random();
    // myNN.print();
    // myNN.initialize_zero();
    myNN.print();
}