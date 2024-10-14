#include "Matrix.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

//------------
//Constructors
//------------
Matrix::Matrix()
    : rows(0), columns(0), beginning_of_matrix_data_pointer(nullptr), index_pointer(nullptr){}

Matrix::Matrix(int rows, int columns)
    : rows(rows), columns(columns), beginning_of_matrix_data_pointer(new float[rows * columns]), index_pointer(nullptr){}
//------------



//-----------
//Destructors
//-----------
Matrix::~Matrix(){
    delete[] beginning_of_matrix_data_pointer;
}
//-----------



//----------------
//Member Functions
//----------------

//Set function
int Matrix::set(int r, int c, float val){
    if(r>=rows || c>=columns){
        return 0;
    }
    else{
        *(beginning_of_matrix_data_pointer+r*columns+c) = val;
        return 1;
    }
}

//Get function
float Matrix::get(int r, int c) const{
    return (*(beginning_of_matrix_data_pointer+r*columns+c));
}

// Copy Constructor
Matrix::Matrix(const Matrix& a)
    : rows(a.rows), columns(a.columns)
{
    // Allocate memory for the matrix data
    this->beginning_of_matrix_data_pointer = new float[rows * columns];
    this->index_pointer = beginning_of_matrix_data_pointer;

    // Copy the data from the other matrix
    memcpy(this->beginning_of_matrix_data_pointer, a.beginning_of_matrix_data_pointer,(rows*columns)*sizeof(float));
}

// Assignment Operator
void Matrix::operator=(const Matrix& a)
{
    //TODO: Make it so that you can only do this if Matrix dimensions agree??
    if (this != &a) // Avoid self-assignment
    {
        // Deallocate existing memory
        delete[] this->beginning_of_matrix_data_pointer;

        // Copy the dimensions
        this->rows = a.rows;
        this->columns = a.columns;

        // Allocate memory for the matrix data
        this->beginning_of_matrix_data_pointer = new float[rows * columns];

        // Copy the data from the other matrix
        memcpy(this->beginning_of_matrix_data_pointer, a.beginning_of_matrix_data_pointer,(rows*columns)*sizeof(float));
    }
    return;
}

//initialize random
void Matrix::initialize_random(){
    srand(time(0));
    for(int i = 0; i<rows; i++){
            for(int j = 0; j<columns; j++){
                set(i, j, float(rand()%101)/100);
            }
    }   
}

//Initialize zero
void Matrix::initialize_zero(){
    for(int i = 0; i<rows; i++){
            for(int j = 0; j<columns; j++){
                set(i, j, 0);
            }
    }       
}
//----------------



//----------------
//Friend Functions
//----------------
Matrix operator+(const Matrix &a,const Matrix &b){
    if((a.rows == b.rows) && (a.columns == b.columns)){
        Matrix m(a.rows, a.columns);
        for(int i = 0; i<a.rows; i++){
            for(int j = 0; j<a.columns; j++){
                m.set(i, j, a.get(i, j) + b.get(i, j));
            }
    }   
        return m;
    }
    else{
        std::cout<<"Error: matrix dimensions do not work for + operation\n";
        exit(1);
    }
}

Matrix operator-(const Matrix &a, const Matrix &b){
    if((a.rows == b.rows) && (a.columns == b.columns)){
        Matrix m(a.rows, a.columns);
        for(int i = 0; i<a.rows; i++){
            for(int j = 0; j<a.columns; j++){
                m.set(i,j, a.get(i,j)-b.get(i,j));
            }
    }   
        return m;
    }
    else{
        std::cout<<"Error: matrix dimensions do not work for + operation\n";
        exit(1);
    }
}

Matrix operator*(const Matrix &a,const Matrix &b){
    float sum;
    if(a.columns == b.rows){
        Matrix m(a.rows, b.columns);
        for(int i = 0; i<a.rows; i++){
            for(int j = 0; j<b.columns; j++){
                sum = 0;
                for(int n = 0; n<a.columns; n++){
                    sum+=(a.get(i,n)*b.get(n,j));
                    if(n != a.columns-1){
                    }
                }
                m.set(i,j, sum);
            }
    }   
        return m;
    }
    else{
        std::cout<<"Error: matrix dimensions do not work for * operation\n";
        exit(1);
    }
}

Matrix operator*(const Matrix &a, int b){
    Matrix m(a.rows, a.columns);
    for(int i = 0; i<a.rows; i++){
        for(int j = 0; j<a.columns; j++){
             m.set(i,j, a.get(i,j)*b);
        }
    }
    return m;
}

Matrix operator*(int a, const Matrix &b){
    Matrix m(b.rows, b.columns);
    for(int i = 0; i<b.rows; i++){
        for(int j = 0; j<b.columns; j++){
             m.set(i,j, b.get(i,j)*a);
        }
    }
    return m;
}

Matrix operator%(const Matrix &a,const Matrix &b){
    if(a.rows != b.rows && a.columns != b.columns){
        std::cout<<"Error: matrix dimensions do not agree for the ";
        exit(1);
    }
    Matrix m(a.rows*b.rows, a.columns*b.columns);
    for(int i = 0; i<a.rows; i++){
        for(int j = 0; j<b.columns; j++){
            m.set(i, j, a.get(i, j)*b.get(i, j));
        }
    }
    return m;
}

Matrix transpose(const Matrix& a) {
    Matrix m(a.columns, a.rows);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.columns; j++) {
            m.set(j, i, a.get(i,j));
        }
    }
    return m;
}

Matrix ReLu(const Matrix& a) {
    Matrix m(a.rows, a.columns);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.columns; j++) {
            float value = a.get(i, j);
            if (value < 0) {
                m.set(i, j, 0);
            } else {
                m.set(i, j, value);
            }
        }
    }
    return m;
}

Matrix step(const Matrix& a){
    Matrix m(a.rows, a.columns);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.columns; j++) {
            float value = a.get(i, j);
            if (value < 0) {
                m.set(i, j, 0);
            } else {
                m.set(i, j, 1);
            }
        }
    }
    return m;
}
//----------------