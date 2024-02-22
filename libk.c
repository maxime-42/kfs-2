#include <stddef.h>
#include <stdint.h>
#include "kernel.h"


#define VGA_WIDTH 80
#define VGA_HEIGHT 80
uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;


void	*kmemset(void *b, int c, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		((char *)(b))[i] = c;
	i++;
	}
	return b;
}

#include <stdint.h>

void hex_to_str(uint32_t addr, char *result) {
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

uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_writechar(char c, char colour)
{
    if (c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void ft_putchar(char c )
{
	terminal_writechar(c, VGA_COLOR_WHITE);
}

void terminal_initialize()
{
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }   
}


size_t strlen(const char* str)
{
    size_t len = 0;
    while(str[len])
    {
        len++;
    }

    return len;
}


void ft_putstr(const char* str)
{
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}



void ft_putstr_color(const char* str, uint32_t color)
{
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++)
    {
        terminal_writechar(str[i], color);
    }
}



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

void				print_addr(char *addr_str, uint32_t addr)
{
	uint32_t		color = VGA_COLOR_WHITE;

	if (addr == GDT_ADDRESS)
		color = VGA_COLOR_GREEN;
	ft_putstr_color(addr_str, color);

}

void				ft_hexdump(void *mem_addr, uint32_t size)
{
	uint32_t		j = 0;
	uint32_t		*ptrAddr = (uint32_t *)mem_addr;	
	uint32_t 		addr = *ptrAddr;
	char			*str = (char *)addr;
	char 			addr_str[9];
	
	while (j < size)
	{
		hex_to_str(addr, addr_str);
		print_addr(addr_str, addr);
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

