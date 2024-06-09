#pragma once

class Matrix{
    public:
        int rows;
        int columns;
        float * beginning_of_matrix_data_pointer;
        float * index_pointer;

        Matrix(float * arr, int rows, int columns);
        Matrix(int rows, int columns);
        int set(int r, int c, float val);
        float get(int r, int c);
        void print();
        void setOnes();
        void setZeros();
        void setIdentity();
        void scaleRow(int,float);
        void swapRows(int,int);
        void addRows(int,float,int);
        void rref();
        //float determinant();
        friend float determinant(Matrix); 
        friend Matrix* operator+(Matrix,Matrix);
        friend Matrix* operator*(Matrix,Matrix);
        friend Matrix* operator*(Matrix,float);
        friend Matrix* operator*(float,Matrix);
        //friend Matrix* operator^(Matrix,int); this is for exponent but not really sure how to do this
        void deleteMatrix();
    protected:

};

//Major Concepts To do:
    //inverse
    //eigenvalues
    //determinant
    //transpose