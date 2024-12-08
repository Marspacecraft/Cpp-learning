
#include <iostream>


template <class T,int __col>
class row
{
public:
	T& operator[](int i)
	{
		return _row[i];
	}

	T operator[](int i) const
	{
		return _row[i];
	}

	T get(int i) const
	{
		return _row[i];
	}
private:
	T _row[__col] = {0};
};

template <class T,int _row,int _col>
class matrix
{
public:
	
	matrix(T* mx)
	{
		for(int i=0;i<_row;i++)
		{
			for(int j=0;j<_col;j++)
			_matrix[i][j] = mx[i*_col+j];
		}
	}
	matrix() = default;

	virtual ~matrix()
	{
		
	}
	row<T,_col> & operator[](int i)
	{
		return _matrix[i];
	}
	row<T,_col>  operator[](int i) const
	{
		return _matrix[i];
	}

	T get(int r,int c) const
	{
		return _matrix[r].get(c);
	}

	row<T,_col> get(int r) const
	{
		return _matrix[r];
	}
	
	template <class T1,int _row1,int _col1>
	friend std::ostream& operator<< (std::ostream&,const matrix<T1,_row1,_col1> &);

	// 矩阵转置
	matrix<T,_col,_row> operator ~() const
	{
		matrix<T,_col,_row> ret;
		for(int i=0;i<_row;i++)
			for(int j=0;j<_col;j++)
				ret[j][i] = _matrix[i].get(j);
		return ret;
	}
private:
	row<T,_col> _matrix[_row];
};

// + 矩阵相加
template <class T,int _row,int _col>
matrix<T,_row,_col> operator+ (const matrix<T,_row,_col>& a, const matrix<T,_row,_col>& b)
{
	matrix<T,_row,_col> ret;

	for(int i =0;i<_row;i++)
	{
		for(int j=0;j<_col;j++)
		{
			ret[i][j] = a.get(i,j) + b.get(i,j);
		}
	}

	return ret;
}

// - 矩阵相减
template <class T,int _row,int _col>
matrix<T,_row,_col> operator- (const matrix<T,_row,_col>& a, const matrix<T,_row,_col>& b)
{
	matrix<T,_row,_col> ret;

	for(int i =0;i<_row;i++)
	{
		for(int j=0;j<_col;j++)
		{
			ret[i][j] = a.get(i,j) - b.get(i,j);
		}
	}

	return ret;
}

template <class T,int _row,int _common,int _col>
matrix<T,_row,_col> operator* (const matrix<T,_row,_common>& a, const matrix<T,_common,_col>& b)
{
	matrix<T,_row,_col> ret;

	for(int i =0;i<_row;i++)
	{
		for(int j=0;j<_col;j++)
		{
			ret[i][j] = 0;
			for(int k=0;k<_common;k++)
				ret[i][j] += a.get(i,k) * b.get(k,j);
		}
	}

	return ret;
}

template <class T,int _row,int _col>
std::ostream& operator<< (std::ostream& out, const matrix<T,_row,_col>& a)
{
	for(int i =0;i<_row;i++)
	{
		out << "[" << a.get(i,0);
		for(int j=1;j<_col;j++)
		{
			out << "\t" << a.get(i,j);
		}
		out << "]"<< std::endl;
	}
	return out;
}


