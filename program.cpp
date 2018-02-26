#include <iostream>
#include <iomanip>
#include <math.h>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

class test{
private:
  int** a;
  int p;
public:

  test(MatrixXf t);
  test(int x);
  void print();
  friend void add(test &b,test &c);
  friend void sub(test &b,test &c);
  friend void div(test &b,test &c);
  void add_eigen(Matrix3f x);
  void sub_eigen(Matrix3f x);
  void div_eigen(Matrix3f x);
  test mat_mult(test B);
  test eig_mult(Matrix3f t);
  int get(int x,int y);
};

  test::test(MatrixXf t)
  {
    p= sqrt(t.size()); //To get the dimensions
    a= new int*[p];    //Declaration of dynamic 2D array
    for(int i=0;i<p;i++)
    {
      a[i]=new int[p];
    }

    for(int r=0;r<p;r++)
    {
      for(int c=r;c<p;c++)
      {
        a[r][c]=t(r,c);
      }
    }

  }

  //Constructor to initialize symmetric matrix without eigen matrix as argument
  //Here argument is taken as integer to specify dimensions
  test::test(int x)
  {
    p= x;
    a= new int*[p];
    for(int i=0;i<p;i++)
    {
      a[i]=new int[p];
    }

    for(int r=0;r<p;r++)
    {
      for(int c=r;c<p;c++)
      {
        a[r][c]=0;
      }
    }
  }

  void test::print()
  {
    for(int x=0;x<p;x++)
    {
        for(int y=0;y<p;y++)
        {
            if(x<=y)
            {
            cout<<setw(4);
            cout<<a[x][y];
            }
            else
            {
              cout<<setw(4)<<" ";
            }
        }
    cout<<endl;
    }
  }

void add(test &b,test &c)
{
  int i, j;
  if(b.p==c.p) //Dimensions check
  {
    int t[b.p][b.p];
    for (i = 0; i < b.p; i++)
          {for (j = i; j < b.p; j++)
              {t[i][j] = c.a[i][j] + b.a[i][j];}
          }
          for(int x=0;x<b.p;x++)
          {
              for(int y=0;y<b.p;y++)
              {
                if(x<=y)
                {
                cout<<setw(4);
                cout<<t[x][y];
                }
                else
                {
                  cout<<setw(4)<<" ";
                }
              }
          cout<<endl;
          }
  }
  else
  {
    cout<<"Dimensions of two matrices don't match"<<endl;
  }
}

void sub(test &b,test &c)
{
  int i, j;
  if(b.p==c.p) //Dimensions check
  {
    int t[b.p][b.p];
    for (i = 0; i < b.p; i++)
          {for (j = i; j < b.p; j++)
              {t[i][j] = c.a[i][j] - b.a[i][j];}
          }
          for(int x=0;x<b.p;x++)
          {
              for(int y=0;y<b.p;y++)
              {
                if(x<=y)
                {
                cout<<setw(4);
                cout<<t[x][y];
                }
                else
                {
                  cout<<setw(4)<<" ";
                }
              }
          cout<<endl;
          }
  }
  else
  {
    cout<<"Dimensions of two matrices don't match"<<endl;
  }
}

void div(test &b,test &c)
{
  int i, j;
  if(b.p==c.p)
  {
    int t[b.p][b.p];
    for (i = 0; i < b.p; i++)
          {for (j = i; j < b.p; j++)
              {t[i][j] = c.a[i][j] / b.a[i][j];}
          }
          for(int x=0;x<b.p;x++)
          {
              for(int y=0;y<b.p;y++)
              {
                if(x<=y)
                {
                cout<<setw(4);
                cout<<t[x][y];
                }
                else
                {
                  cout<<setw(4)<<" ";
                }
              }
          cout<<endl;
          }
  }
  else
  {
    cout<<"Dimensions of two matrices don't match"<<endl;
  }
}

  void test::add_eigen(Matrix3f x)
  {
    int i, j;
    for (i = 0; i < 3; i++)
        {for (j = 0; j < 3; j++)
            {a[i][j] = a[i][j] + x(i,j);}
        }
  }

  void test::sub_eigen(Matrix3f x)
  {
    int i, j;
    for (i = 0; i < p; i++)
        {for (j = 0; j < p; j++)
            {a[i][j] = a[i][j] - x(i,j);}
        }
  }

  void test::div_eigen(Matrix3f x)
  {
    int i, j;
    for (i = 0; i < p; i++)
        {for (j = 0; j < p; j++)
            {a[i][j] = a[i][j] / x(i,j);}
        }
  }

  test test::mat_mult(test B)
  {
    int i, j, k;
    test temp(p);
    for (i = 0; i < p; i++)
    {
        for (j = 0; j < p; j++)
        {
            for (k = 0; k < p; k++)
                {temp.a[i][j] += a[i][k]*B.a[k][j];}
        }
    }
    return temp;
  }

  test test::eig_mult(Matrix3f t)
  {
    int i, j, k;
    test temp(p);
    for (i = 0; i < p; i++)
    {
        for (j = 0; j < p; j++)
        {
            for (k = 0; k < p; k++)
                temp.a[i][j] += a[i][k]*t(k,j);
        }
    }
    return temp;
  }

  int test::get(int x,int y)
  {
    if(x>y)
    {
      int z=x;
      x=y;
      y=z;
      return a[x][y];
    }
    return a[x][y];
  }


int main()
{
    /** Decalaration of 4 dimensional eigen matrix **/
    MatrixXf q(4,4);
    q(0,0)=1;
    q(0,1)=1;
    q(0,2)=2;
    q(0,3)=4;
    q(1,0)=8;
    q(1,1)=5;
    q(1,2)=9;
    q(1,3)=2;
    q(2,0)=2;
    q(2,1)=3;
    q(2,2)=7;
    q(2,3)=6;
    q(3,0)=4;
    q(3,1)=5;
    q(3,2)=5;
    q(3,3)=3;


    /** Declaration of eigen matrix 1 of 3 dimensional.
    We can declare eigen matrix of any dimension but as a
    demonstration I have taken it as 3 dimensional **/
    MatrixXf m(3,3);
    m(0,0)=1;
    m(0,1)=1;
    m(0,2)=2;
    m(1,0)=8;
    m(1,1)=5;
    m(1,2)=9;
    m(2,0)=2;
    m(2,1)=3;
    m(2,2)=7;
    cout<<"Eigen::Matrix 1:"<<endl;
    cout<<m<<endl;
    //Printing Eigen matrix 1

    /** Declaration of eigen matrix 2 of 3 dimensional **/
    Matrix3f n;
    n << 9, 8, 1,
         9, 9, 9,
         7, 8, 9;
    cout<<"Eigen::Matrix 2:"<<endl;
    cout<<n<<endl;
    //Printing of Eigen Matrix 2

    /** Declaration of object of class test.Constructor is called and
    The eigen Matrix is passed as argument  to convert it into a Symmetric Matrix
    by dynamically declaring a 2D array **/
    test t1(m);
    test t2(n);

    //Printing the Symmetric matrices 1 and 2
    cout<<"SymMat 1:"<<endl;
    t1.print();
    cout<<"SymMat 2:"<<endl;
    t2.print();

    /** To add two Symmetric matrices, a friend function is called
    to get the sum of Symmetric matrix 1 and 2.
    For subtraction and division use .sub and .div function respectively**/
    cout<<"Sum:"<<endl;
    add(t1,t2);

    /** To show the dimension error by adding 3 dimensional
    matrix to 4 dimensional. Shows exception **/
    test q1(q);
    cout<<"Sum(Error):"<<endl;
    add(t1,q1);

    /** To add eigen matrix to the symmetric matrix, the function add_eigen
    of object t4 is called and an eigen matrix n is passed as argument.This function
    adds the eigen matrix n to the symmetric matrix of object t4. Similarly
    use sub_eigen and div_eigen for subtraction and division **/
    test t4=t1;
    cout<<"SymMat1 + Eigen::Matrix2 :"<<endl;
    t4.add_eigen(n);
    t4.print();

    /** For matrix multiplication of symmetric matrices of object t1 and t2,
    another object t5 is created to store the result **/
    //Integer argument passed as constructor to specify dimensions of matrix
    test t5(3);
    cout<<"SymMat1 * SymMat2 :"<<endl;
    t5=t1.mat_mult(t2);
    t5.print();

    /** For matrix multiplication of symmetric matrix of object t1 and
    eigen matrix n, another object t6 is created to store the result **/
    //Integer argument passed as constructor to specify dimensions of matrix
    test t6(3);
    cout<<"SymMat1 * Eigen::Matrix2 :"<<endl;
    t6=t1.eig_mult(n);
    t6.print();

    /** To show that accessors for t1(i,j) and t1(j,i) returns the
     same value S(i,j) , the example to t1(2,0) and t1(0,2) is taken.
     We can similarly show for t2 **/
    cout<<"Get t1(2,0):"<<endl;
    cout<<t1.get(2,0)<<endl;
    cout<<"Get t1(0,2):"<<endl;
    cout<<t1.get(0,2)<<endl;

    return 0;

}
