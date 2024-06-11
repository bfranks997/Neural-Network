#pragma once

class Matrix{
    public:
        int rows;
        int columns;
        float * beginning_of_matrix_data_pointer;
        float * index_pointer;

        Matrix(int rows, int columns);
        int set(int r, int c, float val);
        float get(int r, int c) const;
        void print();
        void setOnes();
        void setZeros();
        void scaleRow(int,float);
        void swapRows(int,int);
        void addRows(int,float,int);
        //Matrix operator=(Matrix);
        Matrix operator=(const Matrix &);
        friend Matrix operator+(const Matrix &,const Matrix &);
        friend Matrix operator-(const Matrix &,const Matrix &);
        friend Matrix operator*(const Matrix &,const Matrix &);
        friend Matrix operator*(const Matrix &,float);
        friend Matrix operator*(float,const Matrix &);
        friend Matrix ReLu(const Matrix &);
        //friend Matrix* operator^(Matrix,int); this is for exponent but not really sure how to do this
        void deleteMatrix();
    protected:

};

//Major Concepts To do:
    //inverse
    //eigenvalues
    //determinant
    //transpose