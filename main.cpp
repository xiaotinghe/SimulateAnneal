#include <iostream>  
#include <fstream>
#include <vector>
#include <ctime>  
#include <cstdlib>  
#include <cmath>  
#define INF 9999999  
using namespace std;

class TSP {
private:
	int city;//城市数目
	double loc_distance = 0; //当前距离
	double min_distance = INF; //目前已找到的最短距离
	vector<int> temp; //中间路径
	vector<int> result;//保存目前最优路径
	vector<vector<double>> distance;//城市间距离矩阵
public:
	//存在已有数据文件时
	TSP(int city, int line, string file): temp(city), result(city), distance(city, vector<double>(city, INF)) {
		this->city = city;
		std::ifstream in(file);
		std::cin.rdbuf(in.rdbuf());
		for (int i = 0; i < line; i++)
		{
			int city_a, city_b;
			double k;
			cin >> city_a >> city_b >> k;
			distance[city_a][city_b] = distance[city_b][city_a] = k;//初始化距离矩阵
		}
		for (int i = 0; i < city; i++) {
			temp[i]=i;//初始化路径
			if (i != city -1) {
				loc_distance += distance[i][i + 1];
			}
		}
		loc_distance += distance[city -1][1];//计算初始距离
	}
	//不存在已有数据文件时
	TSP(int city) : temp(city), result(city), distance(city, vector<double>(city, INF)) {
		this->city = city;
		srand((unsigned)time(NULL));
		for (size_t i = 0; i < city -1; i++)
		{
			for (size_t j = i + 1; j < city; j++) {
				float k = (rand() % 10000)/100.0;//随机生成数据
				//cout << i << " " << j << " " << k << endl; 
				distance[i][j] = distance[j][i] = k;//初始化距离矩阵
			}
		}
		for (size_t i = 0; i < city; i++) {
			temp[i] = i;//初始化路径
			if (i != city - 1) {
				loc_distance += distance[i][i + 1];
			}
		}
		loc_distance += distance[city - 1][1];//计算初始距离
	}
	double calculate(int loop = 40 , const double t = 1 , const double delta = 0.999,const double epsilon= 1e-30, const int limit=300000) {
		for (int i = loop; i > 0; i--)
		{
			long count = 0;//迭代步数  
			srand((unsigned)time(NULL));//初始化随机数种子 
			double temperature = t;
			while (temperature > epsilon && count <=limit) {
				int t1 = rand() % (city - 1) + 1, t2 = rand() % (city - 1) + 1;//随机获得两个位置   
				if (t1 != t2) {
					swap(temp[t1], temp[t2]);//交换两位置   
					double ndist = 0;
					for (int j = 0; j<city - 1; j++)ndist += distance[temp[j]][temp[j + 1]];
					ndist += distance[temp[city - 1]][temp[1]];
					double df = (ndist - loc_distance);
					if (df<0) {//当前解更优   
						loc_distance = ndist;
					}
					else if (exp(-df / temperature)>(rand() % 100) / 100.0) {//大于   
						loc_distance = ndist;
					}
					else {
						swap(temp[t1], temp[t2]);
					}
					temperature *= delta;//降温  
				}
				count++;
			}
			cout << "已循环" << loop-i+1 << "次，此次最短距离" << loc_distance << endl;
			if (loc_distance<min_distance) {
				min_distance = loc_distance;
				result.assign(temp.begin(), temp.end());
			}
		}
		cout << "计算完成！" << endl;
		return min_distance;
	}
	vector<int> detail() {
		return result;
	}
};
int main() {
	//第一种形式，指定数据文件，传入参数（城市数目，文件行数，文件名）
	TSP tsp = TSP(35, 595, "input.txt");
	cout<<"最短长度:"<<tsp.calculate()<<endl;
	cout << "路径:";
	auto result = tsp.detail();
	for (auto iter = result.cbegin(); iter != result.cend(); iter++)
	{
		cout << (*iter) << " ";
	}
	cout<<endl;
	
	//第二种形式，不指定数据文件，传入参数（城市数目）
	TSP tsp1 = TSP(10);
	cout << "最短长度:" << tsp1.calculate() << endl;
	cout << "路径:";
	result = tsp1.detail();
	for (auto iter = result.cbegin(); iter != result.cend(); iter++)
	{
		cout << (*iter) << " ";
	}
	return 0;
}
