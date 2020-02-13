#include<iostream>
/*
 *  test static_cast
int main()
{ 
    double i = 3.14;
    int a = static_cast<int>(i);
    std::cout << a << std::endl;
    return 0;
}
*/
/*
 *  test const_cast
int main ()
{
    const int i = 10;
    int *a = const_cast<int*>(&i);
    *a = 100;
    std::cout << i << std::endl;
    return 0;
}

*/

//test dynamic_cast
class A{
  public:
      virtual void f(){}
};
class B :public A{
  public:
      virtual void f1(){}
};

void fun(A* p){
  B*pb1 = static_cast<B*>(p);
  B*pb2 = dynamic_cast<B*>(p);
  std::cout << "pb1:" << pb1 << std::endl;
  std::cout << "pb2:" << pb2 << std::endl;
}

int main()
{
    A a;
    B b;
    fun(&a);
    fun(&b);
    return 0;
}


