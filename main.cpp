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

    myNN.print();
    int choice = 0;
    while(choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4){
        cout<<"Choose what you want to do\n";
        cout<<"0 - Set values to 0\n";
        cout<<"1 - Set values to random\n";
        cout<<"2 - Manually Input value\n";
        cout<<"3 - Set values from file\n";
        cout<<"4 - Save values to a file\n";
        cout<<"Enter anything else to exit\n";
        cin>>choice;
        if(choice == 0){
            myNN.initialize_zero();
        }
        else if(choice == 1){
            myNN.initialize_values_random();
        }
        else if(choice == 2){
            myNN.manual_input_NN();
            //Matrix m(1,1);
            //m.set(0,0,1);
            //myNN.input_NN(m);
        }
        else if(choice == 3){
            myNN.initialize_from_file();
        }
        else if(choice == 4){
            myNN.save_to_file();
        }
        myNN.print();
    }
}