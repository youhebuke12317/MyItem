
# 优先队列(priority_queue)

> 实际上，它的本质就是一个heap
使用头文件：
```
#include <queue>
```

## 简介
```
priority_queue<int>	p1;		// 默认是最大优先级队列 对头为最大元素
priority_queue< int, vector<int>, less<int> >		p2;	 //提前定义好预定义函数 
priority_queue< int, vector<int>, greater<int> >	p3;  //最小优先级队列
```

less与greater是内置仿函数，也可以自定义仿函数, 例如：
```
#include<iostream>
#include<queue>
#include<cstdlib>
using namespace std;
struct Node {
	int x,y;
	Node(int a=0, int b=0):
		x(a), y(b) {}
};

class cmp {
public:
	bool operator()(Node a, Node b){
		if(a.x == b.x)	return a.y>b.y;
		return a.x>b.x;
	}
};

int main() {
	priority_queue<Node, vector<Node>, cmp>p;

	for(int i=0; i<10; ++i)
		p.push(Node(rand(), rand()));

	while(!p.empty()){
		cout<<p.top().x<<' '<<p.top().y<<endl;
		p.pop();
	}

	return 0;
}

```


```
p1.push(33);			// 入队
p1.push(11);
p1.push(55);
p1.push(22);

p1.top();			// 获取对头元素
p1.pop();			// 出队
p1.size();			// 获取队列大小
pi.empty()  		// 如果优先队列为空，则返回真 
	```
