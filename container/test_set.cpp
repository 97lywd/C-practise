#include<set>
#include<iostream>

int main()
{
  //构造
  std::set<int>s;
  //插入
  s.insert(1);
  s.insert(4);
  s.insert(1);
  s.insert(2);
  //使用迭代器遍历元素
  for(auto &e : s){
     std::cout << e << std::endl;
  }
  //删除
  s.erase(1);
  std::cout << s.size() <<std::endl;
  return 0;
}
