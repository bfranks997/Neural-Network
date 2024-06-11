#pragma once
#include "Matrix.h"
//  1) Nodes: These are simply vectors. You need One input vector, one output vector, and then another N vectors (one for each layer)
//  2) Weight Matrices: Matrices, you need N+1 weight matrices (N, one for each layer + 1 for output)

class NeuralNetwork{
    public:
        // int rows;
        // int columns;
        // float * beginning_of_matrix_data_pointer;
        // float * index_pointer;

        //Matrix(float * arr, int rows, int columns);
        //void deleteMatrix();

        Matrix * inputs;
        int num_inputs;
        Matrix * outputs;
        int num_outputs;

        Matrix ** weights;
        Matrix ** biases;
        Matrix ** node_layer;
        int * layer_size_array;
        int number_of_layers;

        int input_NN(Matrix);
        NeuralNetwork(int, int, int, int *, Matrix *, Matrix *, Matrix **, Matrix **, Matrix **
        );

        
    protected:

};