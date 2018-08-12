

map: key - value

map<int, string>	map;

# map插入
```
// 前三种方法返回pair<iterator, bool> 
// 并且若key存在 则插入报错 
// 插入方法1
map.insert(pair<int, string>(1, "teacher01"));
map.insert(pair<int, string>(2, "teacher02"));

// 插入方法2
map.insert(make_pair(3, "teacher03"));
map.insert(make_pair(4, "teacher04"));

// 插入方法3
map.insert(map<int, string>::value_type(5, "teacher05"));

//若key存在 则覆盖之前的value 
//插入方法4
map[6] = "teacher07";
```


# 遍历 -- 迭代器
for (map<int, string>::iterator: it = map.begin(); it != it.end(); it++){
 	it->first;
 	it->second;
}

# 判空	map.empty();

# 删除
map.erase(iterator);

# 查找	
map<int, string>::iterator  it = map.find(100);
if (it == map.end()) {
 	cont << 查找不存在
} else {
 	cout << it.first -> first << "\t" << it.first->second << endl;
}

// 异常处理 
pair< map<int, string>::iterator, map<int, string>::iterator > mypair = map.equal_range(elem); //返回两个迭代器 形成一个pair
 		第一个迭代器 >= elem 的位置
 		第二个迭代器 =  elem 的位置
if (mypair.first == map.end()) {
 	cout << "第一个迭代器 >= elem 的位置不存在"
}


