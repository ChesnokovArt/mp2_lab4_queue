#pragma once

const int MaxMemSize = 100;
typedef int TElem;
typedef TElem* PTElem;

class TStack
{
protected:
	PTElem pMem;
	int MemSize;
	int DataCount;
	int Hi;
	virtual int GetNextIndex(int index);

public:
	TStack(int size);
	~TStack();
	bool isEmpty(void) const { return DataCount == 0; };
	bool isFull(void) const { return DataCount == MemSize; };
	void Put(const TElem& Val);
	int Size() { return DataCount; }
	virtual TElem Get(void);
};

enum class TStackException
{
	Overflow,
	Empty,
	TooLarge,
	NegativeSize
};