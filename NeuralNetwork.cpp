//~let N be the number of layers in our Neural Netowrk
//We need some objects:
//  1) Nodes: These are simply vectors. You need One input vector, one output vector, and then another N vectors (one for each layer)
//  2) Weight Matrices: Matrices, you need N+1 weight matrices (N, one for each layer + 1 for output)

//Idea: we can make a neural network by passing in arguements for a class which are an array pointer containing 
//the sizes of each network layer, the number of layers, the number of inputs, and the number of outputs

//we can then use this data to make the node vectors, weight matrices, and bias matrices.

//Now that I think about it, I think that it may be difficult to adjust and change the biases when they are not all in a single array
//However I can definetely still figure out a way to systematically do this

#include "NeuralNetwork.h"
#include "Matrix.h"

//TODO:
// = assignment operator
//fix the stupid pointer stuff with the matrices. No reason to return a pointer. Just use the pointer to edit
//make a node reset function


//Part 1: Neural Network Functions for Determining Most likely
        // Matrix ** weights;
        // Matrix ** biases;
        // int * layer_size_array;
        // int number_of_layers;
        //Matrix ** node_layer;
int NeuralNetwork::input_NN(Matrix input){

    //Part 1: Reset the Node Values and Input the new Value

    //Part 2: Generate Output from the input
    for(int i = 1; i<(this->number_of_layers); i++){
        //Next Node layer = ReLu(weight_matrix[i]*node_layer[i-1]-bias[i]);
        *((this->node_layer)[i]) = ReLu(*((this->weights)[i-1])*(*(this->node_layer)[i-1] - *((this->biases)[i])));
    }
    
    //Return the Networks Choice
    for(int i = 0; i<num_outputs; i++){

    }
}

NeuralNetwork( int num_inputs, int number_of_layers, int num_outputs, int * layer_size_array,
               Matrix * outputs, Matrix * inputs, Matrix ** weights, Matrix ** biases, Matrix ** node_layer
){

}

