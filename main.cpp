#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
using namespace std;


void input(unsigned int& M, unsigned int& N, unsigned int& K, unsigned int& X)
{
	cout<<"enter M=  ";
	cin>> M;
	cout<<"enter N=  ";
	cin>> N;
	cout<<"enter K=  ";
	cin>> K;
	cout<<"enter X=  ";
	cin>> X;
	cout << "\n";
}

struct  Matrix
{
	unsigned int mat_M;
	unsigned int mat_N;
	unsigned int qan_X;
	int*  mat_array;
	Matrix(const int& M, const int& N, const int& X):mat_M(M), mat_N(N), qan_X(X) 
	{
		
		mat_array= new int[M * N];
	}
	int getNumberMatrixRow()const
	{
		return mat_M;
	}
	int getNumberMatrixCol()const
	{
		return mat_N;
	}
	int getNumberMatrixQan()const
	{
		return qan_X;
	}
	int& operator() (const unsigned int i, const unsigned int j)const
	{
		return mat_array[i * getNumberMatrixCol() + j];
	}
};


struct filereader
{
	const char * filename;
	std::ifstream f;

	filereader(const char* fn):filename(fn)
	{
		f.open( filename, std::ios::in);
	}
	bool read(int& x)
			{
			if(f >> x)
			{
			 return true;
			}
			else
				{
				return false;
				}
			}
	~filereader()
	{
		f.close();
	}
};


void    addMatrix(const Matrix a, const Matrix b, Matrix  c)
{	assert (a.getNumberMatrixCol() == b.getNumberMatrixCol());
	assert (a.getNumberMatrixRow() == b.getNumberMatrixRow());
	assert (a.getNumberMatrixRow() == c.getNumberMatrixRow());
	assert (a.getNumberMatrixCol() == c.getNumberMatrixCol());
	for(int l = 0; l < a.getNumberMatrixQan() ; ++l)
	{
	for(int  i = 0; i < a.getNumberMatrixRow(); ++i)
	{
		for(int j = 0; j < b.getNumberMatrixCol(); ++j)
		{
			c(i,j)=a(i,j)+b(i,j);
			cout << c(i,j) <<" ";
		}
	cout << "\n";
	}
	cout<<"\n add complated \n";
	}
}

void    multMatrix(const Matrix a, const Matrix b, Matrix c)
{	assert (a.getNumberMatrixCol() == b.getNumberMatrixRow());
	assert (a.getNumberMatrixRow() == c.getNumberMatrixRow());
	assert (b.getNumberMatrixCol() == c.getNumberMatrixCol());
	for(int l = 0; l < a.getNumberMatrixQan(); ++l)
	{	
	for(int i = 0; i < a.getNumberMatrixRow(); ++i)
	{
		for(int j = 0; j < b.getNumberMatrixCol(); ++j)
		{
			int s = 0;
			for(int k = 0 ; k < b.getNumberMatrixRow(); ++k)
			{
				s += a(i,k) * b(k,j);
			}	
		c(i,j) = s;
		}
	}
	cout<< "\n mult complated \n";
	}
}

struct  filewriter
{
	const char* filename;
	std::ofstream f;
	filewriter(const char* fn):filename(fn)
	{
		f.open(filename, std::ios::out);
	}
	void writeint(int& i)
	{
		f<<i;
	}
	void writechar(string & c)
	{
		f<<c;
	}
	~filewriter()
	{
		f.close();
	}
};


bool readMatrix(Matrix & to ,  filereader & from )
{
	for(int l = 0; l < to.getNumberMatrixQan(); ++l)
	{
	from.f.ignore();
	for(int i = 0; i < to.getNumberMatrixRow(); ++i)
	{
		int x=0;
		
		for(int j = 0; j < to.getNumberMatrixCol(); ++j)
		{ 
			if(from.read(x))
				{
					to(i,j)=x;
				}
			else
			{
				return false;
			}
		}
	}
	return true;
	}
}

void    writeMatrix(Matrix r,  filewriter & fw)
{
	for(int l = 0; l < r.getNumberMatrixQan(); ++l)
	{
        string str = " ";
	string str1 = "\n";
	for(int i = 0; i < r.getNumberMatrixRow(); i++)
	{
		for(int j = 0; j < r.getNumberMatrixCol(); j++)
		{
			fw.writeint(r(i,j));
			fw.writechar(str);
		}
		fw.writechar(str1);
	}
	fw.writechar(str1);
	}
}




int main()
{
	unsigned int M = 0;
	unsigned int N = 0;
	unsigned int K = 0;
	unsigned int X = 0;
	input(M, N, K, X);
	Matrix  a(M, N, X), b(M, N, X), c(N, K, X), d(N, K, X), t1(M, N, X), t2(N, K, X), f(M, K, X);
	filereader ar("a.txt"), br("b.txt"), cr("c.txt"), dr("d.txt");
	filewriter fw("f.txt");
	readMatrix(a,ar);
	readMatrix(b,br);
	readMatrix(c,cr);
	readMatrix(d,dr);
	addMatrix (a,b,t1); 
	addMatrix (c,d,t2);
	multMatrix(t1,t2,f);
	writeMatrix(f, fw);
	return 0;
}
