#pragma once

#include <vector>

template<typename T>
class Matrix {
	unsigned int rows , cols;
	std::vector<T> data;
public:
	Matrix ( unsigned int rows , unsigned int cols ) ;
	Matrix ( unsigned int rows , unsigned int cols , const T& base ) ;
	Matrix ( const Matrix<T> &other ) ;

	~Matrix ( ) = default ;

	const T &At ( unsigned int row , unsigned int col ) const ;
	T &At ( unsigned int row , unsigned int col ) ;

	inline unsigned int Rows ( ) const { return rows; }
	inline unsigned int Cols ( ) const { return cols; }

	Matrix<T> operator + ( const Matrix<T> &other ) const;
	Matrix<T> operator - ( const Matrix<T> &other ) const;
	Matrix<T> operator * ( const Matrix<T> &other ) const;
};

template<typename T>
class Vector : public Matrix<T> {
	std::vector<T> data;
public:
	Vector ( unsigned int len ) ;
	Vector ( const Vector &other ) ;

	~Vector ( ) = default;
};

template<typename T>
void HELPER_display_matrix ( const Matrix<T> &mat , unsigned int align = 2 ) ;
