#include "Matrix.h"
#include <iostream>

//using namespace std;

Matrix::Matrix(float * arr, int rows, int columns){
    this->beginning_of_matrix_data_pointer = new float[rows*columns];
    this->index_pointer = beginning_of_matrix_data_pointer;
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<columns; j++){
            *(this->index_pointer) = *arr;
            ++arr;
            ++index_pointer;
            }
    }
    this->rows = rows;
    this->columns = columns;
}

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

float Matrix::get(int r, int c){
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

void Matrix::setIdentity(){
    if(rows != columns){
        std::cout<<"Error: matrix is not NxN so it cannot be made into an identity Matrix\n";
        return;
    }
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<columns; j++){
            if(i == j){
                this->Matrix::set(i,j,1);
            }
            else{
                this->Matrix::set(i,j,0);
            }
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

void Matrix::swapRows(int row1, int row2){
    float temp;
    for(int i = 0; i<columns; i++){
        temp = this->get(row2,i);
        this->set(row2,i,(this->get(row1,i)));
        this->set(row1,i,temp);
    }
}


//Steps to do rref
//1) For i=0 to i = N-1 Check the (i,i) position and see if it is 0 or nonzero
//      if it is a nonzero value X then divide that row by 1/X
//      if it is zero loop through the rest of the column with j= i tp j = N-1 (j,i) to find the first nonzero entry. 
//      When you find the first nonzero entry. Swap rows i and j and then divide by X. If you do not find any value
//      that is nonzero, simply skip to the next value of i. But if there is a nonzero value in the column do not
//      continue. Simply go to the next step
//
//2) Once you get a nonzero value. You must start from j = 0 and go through j = N-1 in (j,i) skipping the j=i row.
//      If the value in the (j,i) position is a nonzero value Y. Row j = Row J - Y*Row I. Do this for all rows
void Matrix::rref(){
        int N;
        int index;
        bool all_zeros = false;

        //This if statement makes sure you only check the smallest dimension
        //since the max rank can only be the smallest dimension. We call this number N
        if(rows<columns){
            N = rows;
        }
        else{
            N = columns;
        }
        for(int i = 0; i<N; i++){
            all_zeros = false;
            if(this->get(i,i) != 0){
                this->scaleRow(i,1/(this->get(i,i)));
            }
            else{
                for(int j = i; j<N; j++){
                    if(j == rows){
                        all_zeros == true;
                        break;
                    }
                    if(this->get(j,i) != 0){
                        this->swapRows(i,j);
                        this->scaleRow(i,1/(this->get(i,i)));
                        break;
                    }
                    if(j == N-1){
                        all_zeros = true;
                        break;
                    }
                }
                if(all_zeros){
                    continue;
                }
            }
            for(int k = 0; k<rows; k++){
                if((k == i) || (this->get(k,i) == 0)){
                    continue;
                }
                else{
                    this->addRows(i,-1*this->get(k,i),k);
                }
            }
        }
}

float determinant(Matrix m){
    if(m.rows != m.columns){
        std::cout<<"Error: Matrix must be NxN to have a determinant\n";
        return 0;
    }
    else{
        float det = 0;
        for(int i = 0; i<m.rows; i++){
            
        }
    }
    return 0; //REMOVE THIS LATER
}

Matrix* operator+(Matrix a,Matrix b){
    if((a.rows == b.rows) && (a.columns == b.columns)){
        Matrix *m = new Matrix(a.rows, a.columns);
        for(int i = 0; i<a.rows; i++){
            for(int j = 0; j<a.columns; j++){
                m->set(i,j, a.get(i,j)+b.get(i,j));
            }
    }   
        return m;
    }
    else{
        std::cout<<"Error: matrix dimensions do not work for + operation\n";
        exit(1);
    }
}

Matrix* operator*(Matrix a,Matrix b){
    float sum;
    if(a.columns == b.rows){
        Matrix *m = new Matrix(a.rows, b.columns);
        for(int i = 0; i<a.rows; i++){
            for(int j = 0; j<b.columns; j++){
                sum = 0;
                for(int n = 0; n<a.columns; n++){
                    sum+=(a.get(i,n)*b.get(n,j));
                    if(n != a.columns-1){
                    }
                }
                m->set(i,j, sum);
            }
    }   
        return m;
    }
    else{
        std::cout<<"Error: matrix dimensions do not work for * operation\n";
        exit(1);
    }
}

Matrix* operator*(Matrix a,float b){
        Matrix *m = new Matrix(a.rows, a.columns);
        for(int i = 0; i<a.rows; i++){
            for(int j = 0; j<a.columns; j++){
                m->set(i,j, a.get(i,j)*b);
            }
        }
        return m;
}

Matrix* operator*(float b,Matrix a){
    return a*b;
}

// a x n * n x b
//for a rows 
//  for b columns
//the a,b** position = row(1-a)*column(1 to b)

//add greater than or equal I/O function which has inputs as threshhold voltage and then outputs binary matrix of the same size

void Matrix::deleteMatrix(){
    delete []this->beginning_of_matrix_data_pointer;
}