#include <iostream>
#include <string>
#include "Matrix.h"
#include "NeuralNetwork.h"

using namespace std;


int main(){
    cout<<"--------------------------------------------------------------\n";
    cout<<"Welcome to the Neural Network Program by Bradley Franks V0.0.4\n";
    cout<<"--------------------------------------------------------------\n";

    NeuralNetwork myNN;
    cout<<"Inputs: "<<myNN.num_inputs<<endl;
    cout<<"Outputs: "<<myNN.num_outputs<<endl;
    cout<<"Number of Hidden Layers: "<<myNN.num_hidden_layers<<endl;
    for(int i = 0; i<myNN.num_hidden_layers; i++){
        cout<<"Size of layer "<<i<<": "<<myNN.node_layer[i+1].rows<<" x " <<myNN.node_layer[i+1].columns<<endl;
    }
    cout<<"Learning rate: "<<myNN.learning_rate<<endl;

    int choice = 0;
    while(choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6){
        myNN.print();
        cout<<"Choose what you want to do\n";
        cout<<"0 - Set values to 0\n";
        cout<<"1 - Set values to random\n";
        cout<<"2 - Manually Input value\n";
        cout<<"3 - Set values from file\n";
        cout<<"4 - Save values to a file\n";
        cout<<"5 - Test Neural Netowork\n";
        cout<<"6 - Change learning rate, current rate = "<<myNN.learning_rate<<"\n";
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
        else if(choice == 5){
            int choice = 0;
            while(choice == 0 || choice == 1 || choice == 2){
                myNN.print();
                cout<<"Choose what you want to do\n";
                cout<<"0 - Train XOR (2 inputs)\n";
                cout<<"1 - Test XOR\n";
                cout<<"2 - Train from examples in a folder\n";
                cout<<"Enter anything else to go back\n";
                cin>>choice;
                if(choice == 0){
                    Matrix I0(2,1);
                    I0.set(0,0,0);
                    I0.set(1,0,0);
                    Matrix I1(2,1);
                    I1.set(0,0,0);
                    I1.set(1,0,1);
                    Matrix I2(2,1);
                    I2.set(0,0,1);
                    I2.set(1,0,0);
                    Matrix I3(2,1);
                    I3.set(0,0,1);
                    I3.set(1,0,1);

                    Matrix O0(2,1);
                    O0.set(0,0,1);
                    O0.set(1,0,0);
                    Matrix O1(2,1);
                    O1.set(0,0,0);
                    O1.set(1,0,1);
                    Matrix O2(2,1);
                    O2.set(0,0,0);
                    O2.set(1,0,1);
                    Matrix O3(2,1);
                    O3.set(0,0,1);
                    O3.set(1,0,0);

                    myNN.print();
                    myNN.train(I0,O0);
                    myNN.train(I1,O1);
                    myNN.train(I2,O2);
                    myNN.train(I3,O3);

                    for(int i = 0; i<10000; i++){
                        myNN.train(I0,O0);
                        myNN.train(I1,O1);
                        myNN.train(I2,O2);
                        myNN.train(I3,O3);
                    }
                    myNN.print();
                    cout<<"Finished Training.\n";
                }
                else if(choice == 1){
                    Matrix I0(2,1);
                    I0.set(0,0,0);
                    I0.set(1,0,0);
                    Matrix I1(2,1);
                    I1.set(0,0,0);
                    I1.set(1,0,1);
                    Matrix I2(2,1);
                    I2.set(0,0,1);
                    I2.set(1,0,0);
                    Matrix I3(2,1);
                    I3.set(0,0,1);
                    I3.set(1,0,1);

                    Matrix O0(2,1);
                    O0.set(0,0,1);
                    O0.set(1,0,0);
                    Matrix O1(2,1);
                    O1.set(0,0,0);
                    O1.set(1,0,1);
                    Matrix O2(2,1);
                    O2.set(0,0,0);
                    O2.set(1,0,1);
                    Matrix O3(2,1);
                    O3.set(0,0,1);
                    O3.set(1,0,0);

                    cout<<"Inputting [0,0]\n";
                    myNN.node_layer[0] = I0;
                    myNN.input_NN(0);


                    cout<<"Inputting [0,1]\n";
                    myNN.node_layer[0] = I1;
                    myNN.input_NN(0);


                    cout<<"Inputting [1,0]\n";
                    myNN.node_layer[0] = I2;
                    myNN.input_NN(0);


                    cout<<"Inputting [1,1]\n";
                    myNN.node_layer[0] = I3;
                    myNN.input_NN(0);
                }
                else if(choice == 2){
                    cout<<"Please input files into the Training_Examples folder and give them each a number.\n";
                    cout<<"For example 1.csv 2.csv ... 89.csv.\n";
                    cout<<"You may have to edit the \"train_directory\" function in order to  fit your files format.\n";
                    cout<<"-----------------------------------------------------------------------------------------\n";
                    cout<<"How many files are in the Training_Examples folder?\n";
                    int num_files, num_iterations;
                    cout<<"Number: ";
                    cin>>num_files;
                    cout<<"How many times do you want to loop through the training examples in this folder?\n";
                    cin>>num_iterations;
                    cout<<"\n\nTraining neural network ...\n";
                    for(int i = 0; i<num_iterations; i++){
                        myNN.train_directory(num_files);
                    }
                }
            }


        }
        else if(choice == 6){
            myNN.manually_change_learning_rate();
        }
        
    }
}