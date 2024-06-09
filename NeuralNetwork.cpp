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

