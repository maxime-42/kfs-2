#include "kernel.h"
#include <stdlib.h>


void	kmain()
{
	terminal_initialize();

	init_gdt();
	 //char result[9];
 //
	 uint32_t addr = 0x000007c0;
	 //hex_to_str(addr, result);
	//ft_putstr(result);
	//ft_putstr("\n\n");
	ft_hexdump(&addr, 10);
	
	while(42);

}
