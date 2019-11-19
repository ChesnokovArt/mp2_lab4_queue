#pragma once
#include "TStack.h"
class TQueue : public TStack
{
protected:
	int Li;
	int GetNextIndex(int index);
public:
	TQueue(int size = MaxMemSize) : TStack(size) { Li = 0; }
	TElem Get(void);
	~TQueue();
};

