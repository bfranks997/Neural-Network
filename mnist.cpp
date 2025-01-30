#include <iostream>
#include <string>
#include "Matrix.h"
#include "NeuralNetwork.h"

using namespace std;


int main(){
    cout<<"--------------------------------------------------------------\n";
    cout<<"Welcome to the Neural Network Program by Bradley Franks V0.0.3\n";
    cout<<"--------------------------------------------------------------\n";

    NeuralNetwork myNN;
    cout<<"Inputs: "<<myNN.num_inputs<<endl;
    cout<<"Outputs: "<<myNN.num_outputs<<endl;
    cout<<"Number of Hidden Layers: "<<myNN.num_hidden_layers<<endl;
    for(int i = 0; i<myNN.num_hidden_layers; i++){
        cout<<"Size of layer "<<i<<": "<<myNN.node_layer[i+1].rows<<" x " <<myNN.node_layer[i+1].columns<<endl;
    }
    cout<<"Learning rate: "<<myNN.learning_rate<<endl;

    //train_dataset(int num_epochs, int number_of_training_examples)
    myNN.train_dataset(1, 1);

    cout<<"\n\nDone!\n";


}