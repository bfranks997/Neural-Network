#include "Matrix.h"
#pragma once

class NeuralNetwork{
    public:

        int num_inputs;
        int num_hidden_layers;
        int num_outputs;
        float learning_rate;
        int * hidden_layer_sizes;
        int choice;
        Matrix inputs;
        Matrix * node_layer;
        Matrix * z;
        Matrix * biases;
        Matrix * weights;

        Matrix * weight_matrix_intermediate;
        Matrix * del_prev;
        Matrix * del;


        //Constructors
        NeuralNetwork();
        NeuralNetwork(int, int, int, int*);

        //Destructors
        ~NeuralNetwork();

        //Member Functions
        void initialize_values_random();
        void initialize_zero();
        int input_NN(Matrix);
        void train(Matrix,Matrix);
        void print();
        //NeuralNetwork& operator=(const NeuralNetwork &);

        //Friend Functions
        //friend void swap(NeuralNetwork&, NeuralNetwork&);

        
    protected:

};