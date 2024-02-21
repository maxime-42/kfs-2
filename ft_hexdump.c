#include "kernel.h"

void	print_ascii(char c)
{
	if (c >= 32 && c <= 126) 
		ft_putchar(c);
	else 
		ft_putchar('.');
}


void	ft_print_hex(char c, int i)
{
	const char base[16] = "0123456789abcdef";

	if (i < 8)
	{
		ft_putchar(*(base + c / 16));
		ft_putchar(*(base + c % 16));
		ft_putchar(' ');
	}
	else 
		ft_putstr("   ");
	if ((i + 1) % 8 == 0)
		ft_putchar(' ');
}


void				ft_hexdump(void *mem_addr, uint32_t size)
{
	uint32_t		j = 0;
	uint32_t		*ptrAddr = (uint32_t *)mem_addr;	
	uint32_t 		addr = *ptrAddr;
	char			*str = (char *)addr;
	char 			result[9];

	while (j < size)
	{
		hex_to_str(addr, result);
		ft_putstr(result);
		ft_putchar(' ');
	       	for (uint32_t i = 0 ; i < 16; i++)
			ft_print_hex(str[i], i);

		ft_putchar('|');
	       	for (uint32_t i = 0 ; i < 16; i++)
			print_ascii(str[i]);
		ft_putchar('|');
		ft_putchar('\n');
		j++;
		addr += 16;
		str = (char *)addr;
	}
	(void)addr;
	(void)str;
}

