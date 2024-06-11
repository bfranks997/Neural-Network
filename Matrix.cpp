#include "Matrix.h"
#include <iostream>

//using namespace std;

Matrix::Matrix(int rows, int columns){
    this->beginning_of_matrix_data_pointer = new float[rows*columns];
    this->index_pointer = beginning_of_matrix_data_pointer;
    this->rows = rows;
    this->columns = columns;
}

int Matrix::set(int r, int c, float val){
    if(r>=rows || c>=columns){
        return 0;
    }
    else{
        *(beginning_of_matrix_data_pointer+r*columns+c) = val;
        return 1;
    }
}

float Matrix::get(int r, int c) const{
    return (*(beginning_of_matrix_data_pointer+r*columns+c));
}

void Matrix::print(){
    index_pointer = beginning_of_matrix_data_pointer;
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<columns; j++){
            if(*index_pointer == -0){
                *index_pointer = 0;
            }
            std::cout<<"["<<*index_pointer<<"]";
            ++index_pointer;
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}


void Matrix::setOnes(){
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<columns; j++){
            this->Matrix::set(i,j,1);
        }
    }    
}

void Matrix::setZeros(){
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<columns; j++){
            this->Matrix::set(i,j,0);
        }
    }    
}

void Matrix::scaleRow(int row_index, float scalar){
    for(int i = 0; i<columns; i++){
        this->set(row_index,i,scalar*(this->get(row_index,i)));
    }
}

void Matrix::addRows(int row_index,float scalar, int result_row_index){
    for(int i = 0; i<columns; i++){
        this->set(result_row_index,i,this->get(result_row_index,i)+scalar*(this->get(row_index,i)));
    }
}

Matrix Matrix::operator=(const Matrix &a){
    return a;
}

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

Matrix operator*(const Matrix &a,float b){
        Matrix m(a.rows, a.columns);
        for(int i = 0; i<a.rows; i++){
            for(int j = 0; j<a.columns; j++){
                m.set(i,j, a.get(i,j)*b);
            }
        }
        return m;
}

Matrix operator*(float b,const Matrix &a){
    return a*b;
}

Matrix ReLu(Matrix &a){
    Matrix m(a.rows, a.columns);
    for(int i = 0; i<a.rows; i++){
        for(int j = 0; j<a.columns; j++){
            if(a.get(i,j)<0){
                m.set(i,j, 0);
            }
        }
    }
    return m;
}

// a x n * n x b
//for a rows 
//  for b columns
//the a,b** position = row(1-a)*column(1 to b)

//add greater than or equal I/O function which has inputs as threshhold voltage and then outputs binary matrix of the same size

void Matrix::deleteMatrix(){
    delete []this->beginning_of_matrix_data_pointer;
}