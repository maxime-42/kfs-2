#include "kernel.h"
#include <stdlib.h>
 //
 uint32_t mult_two(uint32_t n)
 {
	return n * 2;
 }
 
void	kmain()
{
	uint32_t eip;
	terminal_initialize();

	GET_EIP( eip); 
	init_gdt();
	uint32_t addr = 0X000007C0 - 32;
	
    	void (*loadedFunction)() = (void (*)())0x000007B0;
	
	char str[] = "hello world lenox";    	
    	copyFunction((void *)mult_two, (void *)loadedFunction, sizeof(mult_two));
	void *ptr = (void *)0x000007D0;
	kmemcpy(ptr, str, sizeof(str));
    	
	print_register();
	ft_putchar('\n');
	ft_hexdump(&addr, 10);
	
	while(42);

}
