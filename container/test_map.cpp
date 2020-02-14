#include<map>
#include<string>
#include <iostream>
int main()
{
   std::map<std::string,std::string>m1;
   //列表初始化
   std::map<std::string,std::string>m2{
      {"1","一"},{"2","二"},{"3","三"}
   };
   std::cout << m2["1"] << std::endl;
   //拷贝构造
   std::map<std::string,std::string>m3(m2);
   std::cout << m3["1"] << std::endl;
   //使用迭代器遍历
   for(auto it = m2.begin(); it != m2.end(); it++){
      std::cout << (*it).first <<"---" << it->second << std::endl;
   }
   //修改
   m2["1"] = "yi";
   //元素个数
   std::cout << m2.size() << std::endl;
   //插入
   //用pair构造键值对，然后调用insert结构
   m2.insert(std::pair<std::string,std::string>("4","四"));
   //也可以用make_pair构造键值对
   m2.insert(std::make_pair("5","五"));
   //删除
   m2.erase("5");
   for(auto it = m2.begin(); it != m2.end(); it++){
      std::cout << (*it).first <<"---" << it->second << std::endl;
   }
   return 0;
}
