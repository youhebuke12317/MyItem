
## 声明与初始化
```
vector<int> vec;        							//声明一个int型向量
vector<int> vec(5);     							//声明一个初始大小为5的int向量
vector<int> vec(10, 1); 							//声明一个初始大小为10且值都是1的向量
vector<int> vec(tmp);   							//声明并用tmp向量初始化vec向量
vector<int> tmp(vec.begin(), vec.begin() + 3);  	// 用向量vec的第0个到第2个值初始化tmp

int arr[5] = {1, 2, 3, 4, 5};   
vector<int> vec(arr, arr + 5);      				// 将arr数组的元素用于初始化vec向量
													// 说明：当然不包括arr[4]元素，末尾指针都是指结束元
													素的下一个元素，这个主要是为了和vec.end()指针统一

vector<int> vec(&arr[1], &arr[4]); 				// 将arr[1]~arr[4]范围内的元素作为vec的初始值
```

## 容器大小操作
```
c.max_size()：	返回向量类型的最大容量（2^30-1=0x3FFFFFFF）
c.capacity()：	返回向量当前开辟的空间大小（<= max_size，与向量的动态内存分配策略相关）。
c.size()：		返回向量中现有元素的个数（<=capacity）。
c.resize(n)：	调整向量的长度使其能容纳n个元素。
c.resize(n,x)：	把向量的大小改为n，所有新元素的初值赋为x。
c.empty()：		如果向量为空，返回真。
```

## 元素的赋值操作
```
c.assign(first,last)：	将迭代器first,last所指定范围内的元素复制到c 中
c.assign(num,val)：		用val的num份副本重新设置c
```

## 元素的访问操作
```
c.at(n)：	等价于下标运算符[]，返回向量中位置n的元素，因其有越界检查，故比[ ]索引访问安全。
c.front()：	返回向量中第一个元素的引用。
c.back()：	返回向量中最后一个元素的引用。
c.begin()：	返回向量中第一个元素的迭代器。
c.end()：	返回向量中最后一个元素的下一个位置的迭代器，仅作结束游标，不可解引用。
c.rbegin()：返回一个反向迭代器，该迭代器指向容器的最后一个元素。
c.rend()：	返回一个反向迭代器，该迭代器指向容器第一个元素前面的位置。
```

## 元素的删除操作
```
c.pop_back()：			删除向量最后一个元素。
c.clear()：				删除向量中所有元素。
c.erase(iter)：			删除迭代器iter所指向的元素，返回一个迭代器指向被删除元素后面的元素。
c.erase(start, end)：	删除迭代器start、end所指定范围内的元素，返回一个迭代器指向被删除元素段后面的元素。
```

## 元素的插入操作
```
c.push_back(x)：			把x插入到向量的尾部。
c.insert(iter, x)：			在迭代器iter指向的元素之前插入值为x的新元素，返回指向新插入元素的迭代器。
c.insert(iter, n, x)：		在迭代器iter指向的元素之前插入n个值为x的新元素，返回void。
c.insert(iter, start, end):	把迭代器start和end所指定的范围内的所有元素插入到迭代器iter所指向的元素之前，返回void。
```

## 元素的交换操作
```
c.reverse()：	反转元素顺序。
c.swap(c2)：	交换2个向量的内容，c和c2 的类型必须相同。
```
