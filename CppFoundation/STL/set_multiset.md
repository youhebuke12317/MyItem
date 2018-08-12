
# 概述
set 集合 元素唯一  自动排序 不能按照[]方式插入数据
 	内部实现是红黑树形式
multiset 集合 元素可以不唯一  自动排序 不能按照[]方式插入数据
 	内部实现是红黑树形式
 	当需要修改时需先删除在添加
```
set<int>				set1;		// 默认是从小到大排序
set<int, less<int>>		set2;
set<int, greater<int>>	set3;		// 从大到小排序
// 注意一下 优先队列中 greater使用时表示小根堆
```

对于复杂的数据类型 该怎么排序（比较）？？？ ------ 见下面讲述的仿函数

```
set1.insert(tmp);		

set<int>::iterator it1 = set1.brgin();
set<int>::iterator it2 = set1.end();

set1.empty();			// 判空
```


# 仿函数
对自定义函数的比较：--- 仿函数 函数对象
```
// 仿函数
struct FunStudent
{
 	bool operator()(const Student &left, const Student &rigth) 
 	{
 		if (left.age < rigth.age) { // 如果左边的小 就返回真 从小到大按年龄
 			return true;
 		} else {
 			return false;
 	}
}

set<Student, FunStudent>		set1;
Student	s1("s1", 31);
Student	s2("s2", 32);

set1.insert(s1);
set1.insert(s2);
// 这时候会根据年龄从小到大排序 
// 当出现年龄相同时  只出现一个


// 因此判断返回值很重要 返回值（对组）pair<iterator, bool>
pair<set<Student, FunStudent>::iterator, bool>	pair1 = set1.insert(s1);
if (pair1.second == true) {
 	cout << "插入成功" << endl; 
} else {
 	cout << "插入失败" << endl;
}
```
 	
# set 的查找
```
 set.find(elem);			查找元素是elem的迭代器
 set.count(elem);		查找元素为elem的个数
 set.lower_bound(elem);	查找大于等于5的元素的迭代器位置
 set.upper_bound(elem);	查找大于    5的元素的迭代器位置

 set.equal_range(elem);	查找 ...

 		// 返回对组pair<iterator, iterator>
 		pair<set<int>::iterator, set<int>::iterator>	mypair;
 		mypair = set.equal_range(5);
 		mypair.first
 		mypair.second
```


# 常见使用接口

## 构造、拷贝、析构

set c

产生一个空的set/multiset，不含任何元素

set c1(op);			// 以op为排序准则，产生一个空的set/multiset
set c1(c2);			// 产生某个set/multiset的副本，所有元素都被拷贝
set c1(beg, end);	// 以区间[beg,end)内的所有元素产生一个set/multiset
set c1(beg, end, op);	// 以op为排序准则，区间[beg,end)内的元素产生一个set/multiset
c.~set()			// 销毁所有元素，释放内存
set<Elem>			// 产生一个set，以(operator <)为排序准则
set<Elem,op>		// 产生一个set，以op为排序准则

##  特殊的搜寻函数

count (elem);		// 返回元素值为elem的个数
find(elem);			// 返回元素值为elem的第一个元素，如果没有返回end()
lower_bound(elem);	// 返回元素值为elem的第一个可安插位置，也就是元素值 >= elem的第一个元素位置
upper_bound (elem);	// 返回元素值为elem的最后一个可安插位置，也就是元素值 > elem 的第一个元素位置
equal_range (elem);	// 返回elem可安插的第一个位置和最后一个位置，也就是元素值==elem的区间

## 赋值

c1 = c2;			// 将c2的元素全部给c1
c1.swap(c2);		// 将c1和c2 的元素互换
swap(c1,c2);		// 同上，全局函数

## 迭代器相关函数

c.begin();			// 返回一个随机存取迭代器，指向第一个元素
c.end();			// 返回一个随机存取迭代器，指向最后一个元素的下一个位置
c.rbegin();			// 返回一个逆向迭代器，指向逆向迭代的第一个元素
c.rend();			// 返回一个逆向迭代器，指向逆向迭代的最后一个元素的下一个位置

## 安插和删除元素

c.insert(elem);			// 插入一个elem副本，返回新元素位置，无论插入成功与否。
c.insert(pos, elem);	// 安插一个elem元素副本，返回新元素位置，pos为收索起点，提升插入速度。
c.insert(beg, end);		// 将区间[beg,end)所有的元素安插到c，无返回值。
c.erase(elem);			// 删除与elem相等的所有元素，返回被移除的元素个数。
c.erase(pos);			// 移除迭代器pos所指位置元素，无返回值。
c.erase(beg,end);		// 移除区间[beg,end)所有元素，无返回值。
c.clear();				// 移除所有元素，将容器清空

