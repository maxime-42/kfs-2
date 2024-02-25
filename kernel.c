#include "kernel.h"


void	kmain()
{

	terminal_initialize();

	 init_gdt();

	set_string();
	set_function();

	ft_putchar('\n');

	uint32_t addr = 0X000007C0 - 32;
	read_to_stack(&addr, 10);
	
	while(42);

}
