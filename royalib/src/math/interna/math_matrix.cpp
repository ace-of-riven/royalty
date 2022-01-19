#include "../math_matrix.h"

#include <algorithm>
#include <assert.h>

#include <iostream>
#include <iomanip>

template class Matrix<double>;
template class Matrix<int>;
template class Matrix<float>;
template class Matrix<char>;
template class Matrix<short>;
template class Matrix<unsigned int>;
template class Matrix<unsigned char>;
template class Matrix<unsigned short>;

#undef min

template<typename T>
Matrix<T>::Matrix ( unsigned int rows , unsigned int cols ) : rows ( rows ) , cols ( cols ) {
	data.resize ( rows * cols , 0 );
}

template<typename T>
Matrix<T>::Matrix ( unsigned int rows , unsigned int cols , const T &base ) : rows ( rows ) , cols ( cols ) {
	data.resize ( rows * cols , 0 ) ;
	for ( unsigned int r = 0; r < std::min ( cols , rows ); r++ ) {
		data [ r * cols + r ] = base;
	}
}

template<typename T>
Matrix<T>::Matrix ( const Matrix &other ) : rows ( other.rows ) , cols ( other.cols ) {
	data = other.data;
}

template<typename T>
const T &Matrix<T>::At ( unsigned int row , unsigned int col ) const {
	assert ( row < rows && col < cols ) ;
	return data [ row * cols + col ];
}

template<typename T>
T &Matrix<T>::At ( unsigned int row , unsigned int col ) {
	assert ( row < rows &&col < cols );
	return data [ row * cols + col ] ;
}

template<typename T>
Matrix<T> Matrix<T>::operator + ( const Matrix<T> &other ) const {
	assert ( rows == other.rows and cols == other.cols ) ;
	Matrix<T> result ( *this );
	for ( unsigned int i = 0; i < other.data.size ( ); i++ )
		result.data [ i ] += other.data [ i ] ;
	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator - ( const Matrix<T> &other ) const {
	assert ( rows == other.rows and cols == other.cols );
	Matrix<T> result ( *this );
	for ( unsigned int i = 0; i < other.data.size ( ); i++ )
		result.data [ i ] -= other.data [ i ];
	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator * ( const Matrix<T> &other ) const {
	assert ( rows == other.cols );
	Matrix<T> result ( rows , other.cols ) ;
	for ( unsigned int i = 0; i < rows; i++ )
	for ( unsigned int j = 0; j < other.cols; j++ )
	for ( unsigned int k = 0; k < cols; k++ )
		result.At ( i , j ) += At ( i , k ) * other.At ( k , j ) ;
	return result;
}

// Vector

template<typename T>
Vector<T>::Vector ( unsigned int len ) : Matrix<T> ( len , 1 ) {
}

template<typename T>
Vector<T>::Vector ( const Vector &other ) : Matrix<T> ( other ) {
}

template void HELPER_display_matrix ( const Matrix<int> &mat , unsigned int align ) ;

// Helper
template<typename T>
void HELPER_display_matrix ( const Matrix<T> &mat , unsigned int align ) {
	for ( unsigned int r = 0; r < mat.Rows ( ); r++ ) {
		for ( unsigned int c = 0; c < mat.Cols ( ); c++ )
			std::cout << std::right << std::setw ( align ) << mat.At ( r , c ) << " " ;
		std::cout << std::endl;
	}
}

