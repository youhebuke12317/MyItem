# 序列式容器

## vector  

内部实现是单向开口的动态数组线性空间 内存增长为原大小的2倍

## list

内部实现是循环双向链表

## deque

内部实现是双向开口的动态数组线性空间 没有容量概念

deque的数据不是存在动态数组中，每个元素数据存储在另一个缓冲区中

动态数组元素相当于存储的内容包括有指向对应缓冲区的指针

当时STL中实现更加复杂，可以先这么理解吧

详细细节见《STL源码剖析》

## stack

先进后出数据结构, 以deque作为缺省情况下的stack底部结构

被称为配接器，不被称为容器, 因为是以底部容器实现的某种结构

不提供迭代器

也可使用list作为stack的底层实现: stack<int, list<int> > stck;

## queue

先进先出数据结构, 以deque作为缺省情况下的deque底部结构

被称为配接器，不被称为容器, 因为是以底部容器实现的某种结构

不提供迭代器 

也可使用list作为stack的底层实现: queue<int, list<int> > que;

## heap - priority_queue

并不属于STL的容器组件, 扮演着优先队列的助手, 即其底层实现

优先队列实现需要一个vector数组以及一组heap算法

优先队列首先是队列 支持从对头出队 从队尾入队 但加入之后会有调整

不提供迭代器

## slist (非标准)

内部实现是单向链表

提供insert_after() 和 erase_after()供单向链表操作的灵活运用

不提供push_back()操作, 但是提供了push_front(), 即实现头插法

# 关联式容器

## set

内部实现是红黑树

所有元素根据键值key自动排序

其实set中键值key即value, 并且不存在相同键值key

set的迭代器是只读迭代器, 即不允许修改键值key

## map

内部实现是红黑树

所有元素根据键值key自动排序

map所有元素都是pair, 即同时拥有key-value, 并且不存在相同键值key

set的迭代器是既不是只读迭代器也不是mutable iterator, 不允许修改键值, 但可以修改实值value

## multiset

multiset的特性与用法和set完全相同, 唯一的差别是它允许键值重复

插入操作是采用红黑树底层的 insert_equal(), 而非insert_unique()

## multimap

multiset的特性与用法和map完全相同, 唯一的差别是它允许键值重复

插入操作是采用红黑树底层的 insert_equal(), 而非insert_unique()

## hashtable (非标准)

内部实现是哈希表(散列表)

hashtable迭代器没有后退操作, 也没有所谓的逆向迭代器

hashtable中也存在类似redis中rehash实现, STL中叫表格重整(resize)

## hash_set (非标准)

内部以hashtable作为底层实现

由于红黑树有自动排序功能, hashtable没有; 所以hash_set没有自动排序功能

其余特性与set类似

## hash_map (非标准)

内部以hashtable作为底层实现

由于红黑树有自动排序功能, hashtable没有; 所以hash_map没有自动排序功能

其余特性与map类似

## hash_multiset

内部以hashtable作为底层实现

由于红黑树有自动排序功能, hashtable没有; 所以hash_multiset没有自动排序功能

其余特性与multiset类似 

## hash_multimap

内部以hashtable作为底层实现

由于红黑树有自动排序功能, hashtable没有; 所以hash_multimap没有自动排序功能

其余特性与multimap类似 




