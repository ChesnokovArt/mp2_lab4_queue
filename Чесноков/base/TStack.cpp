#include "TStack.h"

int TStack::GetNextIndex(int index)
{
	return ++index;
}

TStack::TStack(int size = MaxMemSize)
{
	if (size < 0) throw TStackException::NegativeSize;
	if (size > MaxMemSize) throw TStackException::TooLarge;
	DataCount = 0;
	if (size == 0) size = MaxMemSize;
	MemSize = size;
	pMem = new TElem[MemSize];
	Hi = -1;
}

TStack::~TStack()
{
	delete[] pMem;
}

void TStack::Put(const TElem & Val)
{
	if (isFull()) throw TStackException::Overflow;
	Hi = GetNextIndex(Hi);
	pMem[Hi] = Val;
	DataCount++;
}

TElem TStack::Get(void)
{
	if (isEmpty()) throw TStackException::Empty;
	DataCount--;
	return pMem[Hi--];
}
