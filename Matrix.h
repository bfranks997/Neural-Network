#pragma once

class Matrix{
    public:
        int rows;
        int columns;
        float * beginning_of_matrix_data_pointer;
        float * index_pointer;

        //Constructors
        Matrix();
        Matrix(int, int);
        Matrix(const Matrix &); //copy constructor

        //Destructors
        ~Matrix();

        //Member Functions
        int set(int r, int c, float val);
        float get(int r, int c) const;
        void operator=(const Matrix &); 
        void initialize_random();
        void initialize_zero();
        void print();

        //Friend Functions
        friend Matrix operator+(const Matrix &,const Matrix &); //matrix-matrix addition
        friend Matrix operator-(const Matrix &,const Matrix &); //matrix-matrix subtraction
        friend Matrix operator*(const Matrix &,const Matrix &); //matrix-matrix multiplication
        friend Matrix operator*(const Matrix &, int); //scalar-matrix multiplication
        friend Matrix operator*(int, const Matrix &); //scalar-matrix multiplication
        friend Matrix operator%(const Matrix &,const Matrix &); //Kronecker Product
        friend Matrix transpose(const Matrix &);
        friend Matrix ReLu(const Matrix &); //matrix relu
        friend Matrix step(const Matrix &); //matrix unit step function

        //TODO: Add a Delete Function
};