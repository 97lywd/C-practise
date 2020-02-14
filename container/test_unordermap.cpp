#include<iostream>
#include<unordered_map>
int main()
{
    std::unordered_map<int,int> um;
    //初始化列表插入 initializer list insert
    um.insert({{1,2},{2,4}});
    //拷贝构造
    std::unordered_map<int,int> um2(um);
    //移动构造&插入  move insert
    um2.insert(std::make_pair<int,int>(3,6));
    std::unordered_map<int,int> um3;
    //赋值
    um3 = {{4,8},{5,10}};
    //范围插入 range insert
    um2.insert(um3.begin(),um3.end());
    //删除
    um2.erase(1);
    //迭代器遍历
    for(auto it = um2.begin(); it != um2.end(); it++){
        std::cout << it->first << "---" << it->second << std::endl;
    }
    //访问
    std::cout << um2[2] << std::endl;
    return 0;
}
