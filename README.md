# SimulateAnneal
模拟退火算法求解TSP问题
## 本程序使用 C++实现了通过模拟退火算法求解 TSP 问题 
（为保证开发速度与实际性能，使用了部分 C++11 新特性，编译时请加参数-std=c++11）
### 用法： 
TSP 类包含两个构造函数，分别用于有数据文件、随机生成数据情况。
~~~
TSP(int city, int line, string file) 
city:城市数 
ling:数据文件行数 
file:数据文件名 

TSP(int city) 
city:城市数 
~~~

TSP 类 calculate 方法，通过模拟退火算法计算最短路径长度，返回值为 double类型的最短路径长度
~~~
double calculate(int loop, double t, double delta, double epsilon, const int limit) 
loop 循环次数
t 初始温度 
delta 温度衰减率 
epsilon 最低温度 
limit 限制迭代次数 
~~~

TSP 类 detail 方法，返回一个 vector，包含了最短路径所经节点 
`vector<int> detail() `
 
### 性能测试： 
Intel i5-7200U、8GB 内存、Windows10 操作系统、TDM-GCC 4.9.2，编译选项std=c++11 
算法参数为 loop = 40 , t = 1 , delta = 0.999, epsilon= 1e-30, limit=300000 

城市数 10 20 35 50 
运行时间(ms) 226 256 295 354 
 
