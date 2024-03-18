#include "kernel.h"

uint32_t multi_two(uint32_t n)
{
	return n * 2;
}

void	set_string()
{

	void *ptr = (void *)STRING_ADDRESS;
	char str[] = "hello world lenoxko";    	
	kmemcpy(ptr, str, sizeof(str));


}

void	set_function()
{

	uint32_t eip;
	GET_EIP( eip); 
	void (*ptrFunction)() = (void (*)())MULTI_ADDRESS ;
	//void (*ptrFunction)() = (void (*)())eip;
	copyFunction((void *)multi_two, (void *)ptrFunction, sizeof(multi_two));

}
