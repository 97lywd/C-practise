#include<unordered_set>
#include<iostream>

int main()
{
    std::unordered_set<int> us = {1,1,4,3};
    std::unordered_set<int> us3 = {7,8};
    //copy insert
    std::unordered_set<int> us2(us);
    //range insert
    us2.insert(us3.begin(),us3.end());
    //initializer list insert
    us2.insert({9,10});
    //erase
    us2.erase(1);
    //iterator
    for(auto it = us2.begin(); it != us2.end(); it++){
        std::cout << *it << std::endl;
    }
    return 0;
}
