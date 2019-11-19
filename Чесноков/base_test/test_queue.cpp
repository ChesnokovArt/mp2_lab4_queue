#include <gtest.h>
#include "TQueue.h"
#include "TStack.h"
#include "TQueue.cpp"
#include "TStack.cpp"

TEST(TQueue, can_create_queue)
{
	EXPECT_NO_THROW(TQueue(20));
}

TEST(TQueue, throws_when_create_queue_with_negative_size)
{
	EXPECT_ANY_THROW(TQueue(-2));
}

TEST(TQueue, throws_when_create_queue_with_too_large_size)
{
	EXPECT_ANY_THROW(TQueue(102));
}

TEST(TQueue, valid_size)
{
	TQueue q(3);
	q.Put(1);
	q.Put(2);
	q.Put(3);
	EXPECT_EQ(q.Size(), 3);
}

TEST(TQueue, first_in_first_out)
{
	TQueue q(3);
	q.Put(1);
	q.Put(2);
	q.Put(3);
	EXPECT_EQ(q.Get(), 1);
	EXPECT_EQ(q.Get(), 2);
	EXPECT_EQ(q.Get(), 3);
}

TEST(TQueue, throws_when_overflow)
{
	TQueue q(3);
	q.Put(1);
	q.Put(2);
	q.Put(3);
	EXPECT_ANY_THROW(q.Put(4));
}

TEST(TQueue, throws_when_get_from_empty_queue)
{
	TQueue q(3);
	EXPECT_ANY_THROW(q.Get());
}