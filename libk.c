#include <stddef.h>
#include <stdint.h>
#include "kernel.h"


#define VGA_WIDTH 80
#define VGA_HEIGHT 80
uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

 void copyFunction(void *srcFunction, void *destFunction, size_t size) {
    // Assuming destFunction is the address where you want to copy the source function
    // This is a simplified example, and it might not work on all platforms

    // Copy the bytes of the function from source to destination
    uint8_t* src = (uint8_t*)srcFunction;
    uint8_t* dest = (uint8_t*)destFunction;

    // Assuming the function size is fixed, adjust this accordingly

    for (size_t i = 0; i < size ; ++i) {
        dest[i] = src[i];
    }
}


void print_register()
{
  unsigned int ebp, esp, eip, ecx, edx, ebx, eax, esi, edi;

    GET_EBP(ebp);
    GET_ESP(esp);
    GET_EIP(eip);
    GET_ECX(ecx);
    GET_EDX(edx);
    GET_EBX(ebx);
    GET_EAX(eax);
    GET_ESI(esi);
    GET_EDI(edi);

    ft_putstr(itoa_base(ebp, 16));
    ft_putchar('\n');
    ft_putstr(itoa_base(esp, 16));
    ft_putstr(itoa_base(eip, 16));
    ft_putchar('\n');
    ft_putstr(itoa_base(ecx, 16));
    ft_putchar('\n');
    ft_putstr(itoa_base(edx, 16));
    ft_putchar('\n');
    ft_putstr(itoa_base(ebx, 16));
    ft_putchar('\n');
    ft_putstr(itoa_base(eax, 16));
    ft_putchar('\n');
    ft_putstr(itoa_base(esi, 16));
    
    ft_putchar('\n');
    ft_putstr(itoa_base(edi, 16));
}


void	*kmemset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)b;
	while (len--)
		*p++ = (unsigned char)c;
	return (b);
}


void	*kmemcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	p_src = (unsigned char *)src;
	p_dest = (unsigned char *)dest;
	if (dest == src)
		return (dest);
	while (n--)
		*(p_dest++) = *(p_src++);
	return (dest);
}



char	*itoa_base(int num, int base)
{
    static char text[33];  // Max length for 32-bit integer in binary + null terminator
    int loc = 32;
	kmemset(&text, 0, sizeof(text));
    if (num == 0)
    {
        text[--loc] = '0';
    }
    else
    {
        int neg = 0;
        if (num < 0)
        {
            neg = 1;
            num = -num;
        }
        while (num)
        {
            int remainder = num % base;
            text[--loc] = (remainder < 10) ? ('0' + remainder) : ('A' + remainder - 10);
            num /= base;
        }
        if (neg)
            text[--loc] = '-';
    }
    return &text[loc];
}



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
	//char			*ptr = NULL;

	ptrAddr[8] = 'B';	
	while (j < size)
	{
		hex_to_str(addr, addr_str);
		//ptr = itoa_base(addr, 16);
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

