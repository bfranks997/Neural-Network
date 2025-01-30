#include "Matrix.h"
#include <iostream>
//#include <cstdlib>
#include <fstream>
#include <sstream>
#include <random>
#include <string>

using namespace std;

//------------
//Constructors
//------------
Matrix::Matrix()
    : rows(0), columns(0), beginning_of_matrix_data_pointer(nullptr), index_pointer(nullptr){}

//READ MATRIX IN FROM CSV of known size
Matrix::Matrix(int rows, int columns, string filepath) 
    : rows(rows), columns(columns), beginning_of_matrix_data_pointer(new float[rows * columns]), index_pointer(nullptr){

    ifstream inputFile; //file reader object
    inputFile.open(filepath); //open file that contains Network Parameters TODO: make this adjustable
    
    string line = "";
    string tempString;
    
    float weight = 0;
    //Parse the lines (1 line per hidden layer +1)

    line = "";
    for(int j = 0; j<rows; j++){
        getline(inputFile,line); //First set of actual data is on seventh line in the form: <number of hidden layers>, <number of outputs>
        stringstream inputString(line); //For parsing csv
        for(int k = 0; k<columns; k++){
            getline(inputString, tempString, ',');
            cout<<tempString<<" ";
            if(k==columns-1){
                cout<<"\n";
            }
            weight = stof(tempString);
            this->set(j*columns+k,1,weight); //THIS IS FOR THE MNIST DATASET
            //this->set(j,k,weight);
        }
    }
     //TODO: finish this --> Note the code above does not necessarily work
    inputFile.close();
}

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
    //Delete Old memory
    // if (this != &a){
    //     delete[] beginning_of_matrix_data_pointer;
    // }

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
    std::random_device rd;

    // Use the Mersenne Twister random number generator
    std::mt19937 gen(rd());

    // Define the range for random numbers
    std::uniform_int_distribution<> distr(1, 101);
    
    for(int i = 0; i<rows; i++){
            for(int j = 0; j<columns; j++){
                set(i, j, float(distr(gen)%101)/float(100));
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

//Print Matrix
void Matrix::print() const{
    for(int i = 0; i<rows; i++){
            for(int j = 0; j<columns; j++){
                std::cout<<"["<<get(i,j)<<"]";
            }
            std::cout<<"\n";
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
        std::cout<<"Matrix A: "<<a.rows<<" x "<<a.columns<<"\n";
        std::cout<<"Matrix B: "<<b.rows<<" x "<<b.columns<<"\n";
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
        std::cout<<"Error: matrix dimensions do not work for - operation\n";
        std::cout<<"Matrix A: "<<a.rows<<" x "<<a.columns<<"\n";
        a.print();
        std::cout<<"Matrix B: "<<b.rows<<" x "<<b.columns<<"\n";
        b.print();
        
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
        std::cout<<"Matrix A: "<<a.rows<<" x "<<a.columns<<"\n";
        a.print();
        std::cout<<"Matrix B: "<<b.rows<<" x "<<b.columns<<"\n";
        b.print();
        
        exit(1);
    }
}

Matrix operator*(const Matrix &a, float b){
    Matrix m(a.rows, a.columns);
    for(int i = 0; i<a.rows; i++){
        for(int j = 0; j<a.columns; j++){
             m.set(i,j, a.get(i,j)*b);
        }
    }
    return m;
}

Matrix operator*(float a, const Matrix &b){
    Matrix m(b.rows, b.columns);
    for(int i = 0; i<b.rows; i++){
        for(int j = 0; j<b.columns; j++){
             m.set(i,j, b.get(i,j)*a);
        }
    }
    return m;
}

//Haddamard Product
Matrix operator%(const Matrix &a,const Matrix &b){
    if(a.rows != b.rows || a.columns != b.columns){
        std::cout<<"Error: matrix dimensions do not agree for the haddamard product operator\n";
        std::cout<<"Matrix A: "<<a.rows<<" x "<<a.columns<<"\n";
        a.print();
        std::cout<<"Matrix B: "<<b.rows<<" x "<<b.columns<<"\n";
        b.print();
        exit(1);
    }
    Matrix m(a.rows, a.columns);
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