/**
* @file			UnlockQueue.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月14日 星期二 19时13分03秒
*/

#include <iostream>
#include <cstring>
#include "UnlockQueue.h"
using namespace std;

/*
 * 在构造函数中，未给buffer分配内存，而在Initialize中分配，这样做的原因是：
 * 我们知道在new UnlockQueue的时候有两步操作，第一步分配内存，第二步调用构造函数，
 * 如果将buffer的分配放在构造函数中，那么就可能 buffer 就可能分配失败，
 * 而后面用到buffer，还需要判空。
 * */
UnlockQueue::UnlockQueue(int nSize) : m_pBuffer(NULL), m_nSize(nSize), m_nIn(0), m_nOut(0) {
	//round up to the next power of 2
	if (!is_power_of_2(nSize)) {
		m_nSize = roundup_power_of_two(nSize);
	}
}

UnlockQueue::~UnlockQueue()
{
	if(NULL != m_pBuffer)
		delete[] m_pBuffer;
	m_pBuffer = NULL;
}

bool UnlockQueue::Initialize()
{
	m_pBuffer = new unsigned char[m_nSize];
	if (!m_pBuffer)  return false;
	m_nIn = m_nOut = 0;
	return true;
}

/*
 * 在构造函数中，对传入的size进行2的次幂圆整，圆整的好处是可以将m_nIn % m_nSize 可以
 * 转化为 m_nIn  & (m_nSize – 1)，取模运算”的效率并没有 “位运算” 的效率高。
 * */
unsigned long UnlockQueue::roundup_power_of_two(unsigned long val) {
	// 判断val是否是2的次幂
	if((val & (val-1)) == 0)
		return val;

	unsigned long maxulong = (unsigned long)((unsigned long) ~0);	// 0X7FFFFFFF
	unsigned long andv = ~ ( maxulong & (maxulong >> 1));			// 0X80000000
	while( (andv & val) == 0)
		andv = andv >> 1;

	return andv << 1;
}

unsigned int UnlockQueue::Put(const unsigned char *buffer, unsigned int len) 
{
	unsigned int l;

	len = std::min(len, m_nSize - m_nIn + m_nOut);

	/*
	 * Ensure that we sample the m_nOut index -before- we
	 * start putting bytes into the UnlockQueue.
	 */
	__sync_synchronize();

	/* first put the data starting from fifo->in to buffer end */
	l = std::min(len, m_nSize - (m_nIn  & (m_nSize - 1)));
	memcpy(m_pBuffer + (m_nIn & (m_nSize - 1)), buffer, l);

	/* then put the rest (if any) at the beginning of the buffer */
	memcpy(m_pBuffer, buffer + l, len - l);

	/*
	 * Ensure that we add the bytes to the kfifo -before-
	 * we update the fifo->in index.
	 */
	__sync_synchronize();

	m_nIn += len;

	return len;
}

unsigned int UnlockQueue::Get(unsigned char *buffer, unsigned int len) 
{
	unsigned int l;

	len = std::min(len, m_nIn - m_nOut);

	/*
	 * Ensure that we sample the fifo->in index -before- we
	 * start removing bytes from the UnlockQueue.
	 * 在我们开始从kfifo中删除字节之前, 确保我们采样“UnlockQueue -> in”索引
	 */
	__sync_synchronize();

	/* first get the data from UnlockQueue->out until the end of the buffer */
	/* 首先从UnlockQueue -> out获取数据直到缓冲区结束 */
	l = std::min(len, m_nSize - (m_nOut & (m_nSize - 1)));
	memcpy(buffer, m_pBuffer + (m_nOut & (m_nSize - 1)), l);

	/* then get the rest (if any) from the beginning of the buffer */
	/* 然后从缓冲区的开头得到其余的（如果有的话） */
	memcpy(buffer + l, m_pBuffer, len - l);

	/*
	 * Ensure that we remove the bytes from the kfifo -before-
	 * we update the fifo->out index.
	 */
	__sync_synchronize();

	m_nOut += len;

	return len;
}
int main() {
	return 0;
}
