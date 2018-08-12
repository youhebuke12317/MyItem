# deque容器
deque容器是C++ STL中的内容。

deque与vector类似，支持随机访问和快速插入删除。

deque还支持从开始端加入数据:push_front()

# 构造函数
```
deque<Elem> d;			//创建一个空的deque
deque<Elem> d1(d2);		//复制一个deque
~deque<Elem>();			//销毁所有数据，释放内存
```

# 成员函数
## 迭代器操作
```
deque.begin();		//返回指向第一个元素的迭代器
deque.end();		//返回指向最后一个元素下一个位置的迭代器
deque.rbegin();
deque.rend();		//反向迭代器
```
```
#include <cstdio>
#include <deque>
using namespace std;
int main()
{
	deque<int> d;
	d.push_back(1);d.push_front(2);
	deque<int>::iterator it;
	for(it = d.begin() ; it != d.end() ; it ++) {
		printf("%d\n",*it);
	}	//输出2 1
	return 0;
}
```
## 支持随机访问
```
d.at(pos);	//返回索引为pos的位置的元素
d[pos];		//或者直接这样
```
```
deque<int> d;
d.push_back(1);d.push_front(2);
printf("%d\n",d.at(1));//输出1
printf("%d\n",d[1]);//输出1
```

## 插入和删除
```
deque.erase(pos);		// 删除pos位置的元素
deque.push_back(num);	// 在末尾插入元素
deque.pop_back();		// 弹出末尾的元素
deque.pop_front();		// 删除开头位置的元素
```

## 其余操作
```
deque.empty();	//判断deque是否空
deque.front();	//返回第一个元素
deque.back();	//返回最后一个元素
deque.size();	//返回容器大小
deque.clear();	//清除deque
```

