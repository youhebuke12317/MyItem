/*************************************************************************
    > File Name: static.c
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 六  4/21 00:22:20 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

/*
 * static 成员变量 成员函数
 * 全局函数 与 成员函数
 * 指针 引
 * */

class Goods
{
	public :
		Goods ( int  w) { 
			weight = w ;  
			total_weight += w ; 
		}

		~ Goods() { 
			total_weight -= weight ; 
		}

		int  Weight() { 
			return  weight ; 
		} 

		static  int  TotalWeight() { 
			return  total_weight ; 
		}

		Goods *next ;
	private :
		int  weight ;
		static  int  total_weight ;
};

int  Goods::total_weight = 0 ;

//r尾部指针
void purchase( Goods * &f, Goods * &r, int w )
{
	Goods *p = new Goods(w) ;
	
	p -> next = NULL ;
	
	if ( f == NULL ) {
		f = r = p ;
	}

	else {			// 尾部指针下移或新结点变成尾部结点
		r -> next = p ;  
		r = r -> next ; 
	} 
}

void sale( Goods * & f , Goods * & r )
{
	if ( f == NULL ) { 
		cout << "No any goods!\n" ; 
		return ; 
	}

	Goods *q = f ;
	f = f -> next ;
	delete q ;

	cout << "saled.\n" ;
}

int main()
{
	Goods * front = NULL , * rear = NULL ;
	int  w ; 
	int  choice ;
	
	do {
		cout << "Please choice:\n" ;
		cout << "Key in 1 is purchase,\nKey in 2 is sale,\nKey in 0 is over.\n" ;
	
		cin >> choice ;
		
		switch ( choice )		// 操作选择
		{
			case 1 :								// 键入1，购进1箱货物
				{  
					cout << "Input weight: " ;
					cin >> w ;
					purchase( front, rear, w ) ;        // 从表尾插入1个结点
					break ;
				}
			case 2 :								// 键入2，售出1箱货物
				{ 
					sale( front, rear ) ;				// 从表头删除1个结点
					break ;
				}										
			case 0 : 
				break ;								// 键入0，结束
		}

		cout << "Now total weight is:" << Goods::TotalWeight() << endl ;
	
	} while ( choice ) ;

	return 0;
}


