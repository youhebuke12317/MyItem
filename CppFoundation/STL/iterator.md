## 概述

迭代器是一种检查容器内元素并遍历元素的数据类型。

C++更趋向于使用迭代器而不是下标操作，因为标准库为每一种标准容器（如vector）定义了一种迭代器类型，

而只用少数容器（如vector）支持下标操作访问容器元素。

## 定义和初始化

每种容器都定义了自己的迭代器类型，如vector:
```
vector<int>::iterator    iter;    //定义一个名为iter的变量
```

每种容器都定义了一对名为begin和en的函数，用于返回迭代器。下面对迭代器进行初始化操作：
```
vector<int>    ivec;
vector<int>::iterator    iter1=ivec.bengin();    //将迭代器iter1初始化为指向ivec容器的第一个元素
vector<int>::iterator   iter2=ivec.end();    //将迭代器iter2初始化为指向ivec容器的最后一个元素的下一个位置
```

> 注意end并不指向容器的任何元素，而是指向容器的最后元素的下一位置，称为超出末端迭代器。
> 如果vector为空，则begin返回的迭代器和end返回的迭代器相同。一旦向上面这样定义和初始化，
> 就相当于把该迭代器和容器进行了某种关联，就像把一个指针初始化为指向某一空间地址一样。

## 常用操作
```
*iter          // 对iter进行解引用，返回迭代器iter指向的元素的引用
iter->men      // 对iter进行解引用，获取指定元素中名为men的成员。等效于 (*iter).men
++iter         // 给iter加1，使其指向容器的下一个元素
iter++
--iter         // 给iter减1，使其指向容器的前一个元素
iter--
iter1==iter2   // 比较两个迭代器是否相等，当它们指向同一个容器的同一个元素或者都指向同同一个容器的超出末端的下一个位置时，它们相等 
iter1!=iter2  
```

假设已经声明一个vector<int>的ivec容器，下面用迭代器来遍历ivec容器，把其每个元素重置为0：
```
for(vector<int>::iterator iter = ivec.begin(); iter != ivec.end(); ++iter)
	*iter=0;
```

在C++定义的容器类型中，只有vector和queue容器提供迭代器算数运算和除!=和==之外的关系运算：
```
iter + n     		// 在迭代器上加（减）整数n，将产生指向容器中前面（后面）第n个元素的迭代器。
						新计算出来的迭代器必须指向容器中的元素或超出容器末端的下一个元素
iter - n

iter1 += iter2      // 将iter1加上或减去iter2的运算结果赋给iter1。两个迭代器必须指向容器中的元
						素或超出容器末端的下一个元素
iter1 -= iter2

iter1 - iter2       // 两个迭代器的减法，得出两个迭代器的距离。两个迭代器必须指向容器中的元素或
						超出容器末端的下一个元素

>, >=, <, <=        // 元素靠后的迭代器大于靠前的迭代器。两个迭代器必须指向容器中的元素或超出容
						器末端的下一个元素
```

注意两个迭代器相减得出两个迭代器对象的距离，该距离名为difference_type的signed类型的值，
该类型类似于size_type类型，也是有vector定义的。可以迭代器算术操作来移动迭代器直接指向某个元素：

```
vector<int>::iterator    mid=v.begin()+v.size()/2;    //初始化mid迭代器，使其指向v中最靠近正中间的元素
```

## 迭代器const_iterator

每种容器还定义了一种名为const_iterator的类型。该类型的迭代器只能读取容器中的元素，不能用于改变其值。
之前的例子中，普通的迭代器可以对容器中的元素进行解引用并修改，

而const_iterator类型的迭代器只能用于读不能进行重写。例如可以进行如下操作：

```
for(vector<int>::const_iterator iter=ivec.begin();iter!=ivec.end();++iter)
	cout<<*iter<<endl;       //合法，读取容器中元素值

for(vector<int>::const_iterator iter=ivec.begin();iter!=ivec.end();++iter)
	*iter=0;        //不合法，不能进行写操作
```

const_iterator和const  iterator是不一样的，

后者对迭代器进行声明时，必须对迭代器进行初始化，并且一旦初始化后就不能修改其值。

这有点像常量指针和指针常量的关系。例如：

```
vector<int>    ivec(10);
const    vector<int>::iterator    iter=ivec.begin();
*iter=0;    //合法，可以改变其指向的元素的值
++iter;    //不合法，无法改变其指向的位置
```

## 使迭代器失效的操作

> 由于一些对容器的操作如删除元素或移动元素等会修改容器的内在状态，这会使得原本指向被移动元素的迭代器失效，
也可能同时使其他迭代器失效。使用无效的迭代器是没有定义的，可能会导致和使用悬垂指针相同的问题。所以在使用迭
代器编写程序时，需要特别留意哪些操作会使迭代器失效。使用无效迭代器会导致严重的运行时错误。
