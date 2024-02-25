
#include "kernel.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 80



static void hex_to_str(uint32_t addr, char *result) {
    // Define the hexadecimal characters
    const char hex_chars[] = "0123456789ABCDEF";

    // Iterate through each nibble (4 bits) of the address
    for (int i = 7; i >= 0; --i) {
        // Extract the current nibble
        uint8_t nibble = (addr >> (i * 4)) & 0xF;

        // Convert the nibble to its corresponding hexadecimal character
        result[7 - i] = hex_chars[nibble];
    }

    // Null-terminate the string
    result[8] = '\0';
}


static void	print_ascii(char c)
{
	if (c >= 32 && c <= 126) 
		ft_putchar(c);
	else 
		ft_putchar('.');
}


static void	ft_print_hex(char c, int i)
{
	const char base[16] = "0123456789abcdef";

	if (i < 8)
	{
		ft_putchar(*(base + c / 16));
		ft_putchar(*(base + c % 16));
		ft_putchar(' ');
	}
	else 
		//ft_putstr("   ");
		ft_putstr("  ");
	if ((i + 1) % 8 == 0)
		ft_putchar(' ');
}

static void				print_name(uint32_t addr)
{

	//uint32_t		color = VGA_COLOR_WHITE;
	if (addr == 0x000007D0)
	{	
		ft_putstr("string   ");
	}
	else if (addr == 0x000007B0)
	{
		ft_putstr("multi    ");
	}
	else if (addr == GDT_ADDRESS)
	{
		ft_putstr("GDT      ");
	}
	else
	{
		ft_putstr(".......  ");
	}
}

static void				set_color(uint32_t addr)
{

	if (addr == MULTI_ADDRESS ||  addr == STRING_ADDRESS || addr == GDT_ADDRESS)
	{	
		g_color = VGA_COLOR_GREEN;
	}
	else
	{
		g_color = VGA_COLOR_WHITE;
	}
}

void				read_to_stack(void *mem_addr, uint32_t size)
{
	uint32_t		j = 0;
	uint32_t		*ptrAddr = (uint32_t *)mem_addr;	
	uint32_t 		addr = *ptrAddr;
	char			*str = (char *)addr;
	char 			addr_str[9];

	while (j < size)
	{
		set_color(addr);
		hex_to_str(addr, addr_str);
		//ptr = itoa_base(addr, 16);
		ft_putstr(addr_str);
		ft_putchar(' ');
	       	print_name(addr);
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

