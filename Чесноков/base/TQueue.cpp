#include "TQueue.h"

int TQueue::GetNextIndex(int index)
{
	return (++index) % MemSize;
}

TElem TQueue::Get(void)
{
	if (isEmpty()) throw TStackException::Empty;
	TElem tmp = pMem[Li];
	Li = GetNextIndex(Li);
	DataCount--;
	return tmp;
}

TQueue::~TQueue()
{
}
