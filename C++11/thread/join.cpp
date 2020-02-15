#include<iostream>
#include<thread>
int main()
{
    int n1 = 500;
    int n2 = 600;
    std::thread t([&](int addnum){
            n1 += addnum;
            n2 += addnum;
             },500);
    t.join();
    std::cout << n1 << " " << n2 << std::endl;  
    return 0;
}

