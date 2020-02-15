#include <iostream>
#include <thread>
void foo(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
int main()
{
    std::thread t(foo);
    std::cout << "before join,joinable=" << t.joinable() << std::endl;
    t.join();
    std::cout << "after join ,joinable=" << t.joinable() << std::endl;
    return 0;
}

