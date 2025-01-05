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
        Matrix correct_output;
        Matrix inputs;
        Matrix * node_layer;
        Matrix * z;
        Matrix * biases;
        Matrix * weights;

        //Constructors
        NeuralNetwork();
        NeuralNetwork(int, int, int, int*);

        //Destructors
        ~NeuralNetwork();

        //Member Functions
        void initialize_values_random();
        void initialize_zero();
        void initialize_from_file();
        void save_to_file();
        int input_NN(int i);
        void manual_input_NN();
        void train(Matrix,Matrix); //Train where you need to input the I/O as parameters
        void train(); //Train with I/O already entered in
        void train_directory(int);
        void print();
        void manually_change_learning_rate();
        void change_learning_rate(float);
        void print_line(int, int);
        //float cost();
        //NeuralNetwork& operator=(const NeuralNetwork &);

        //Friend Functions
        //friend void swap(NeuralNetwork&, NeuralNetwork&);

        
    protected:

};