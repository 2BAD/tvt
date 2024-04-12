#ifndef _MY_ASSERT_H_
#define _MY_ASSERT_H_
#include <assert.h>
template<typename T>
void MyAssert(T B)
{
#ifdef __ENVIRONMENT_WIN32__
	assert(B);	
#endif
	return;
}
#endif