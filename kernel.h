#include <stdint.h>
#include <stddef.h>
#ifndef GDT_H
# define GDT_H


#define GET_EBP(x) __asm__ volatile("mov %%ebp, %0" : "=r"(x)::)
#define GET_ESP(x) __asm__ volatile("mov %%esp, %0" : "=r"(x)::)
#define GET_EIP(x) __asm__ volatile("movl $1f, %0; 1:" : "=r"(x))

//#define GET_EIP(x) __asm__ volatile("mov %%eip, %0" : "=r"(x)::)
#define GET_ECX(x) __asm__ volatile("mov %%ecx, %0" : "=r"(x)::)
#define GET_EDX(x) __asm__ volatile("mov %%edx, %0" : "=r"(x)::)
#define GET_EBX(x) __asm__ volatile("mov %%ebx, %0" : "=r"(x)::)
#define GET_EAX(x) __asm__ volatile("mov %%eax, %0" : "=r"(x)::)
#define GET_ESI(x) __asm__ volatile("mov %%esi, %0" : "=r"(x)::)
#define GET_EDI(x) __asm__ volatile("mov %%edi, %0" : "=r"(x)::)


#define SEG_DESCTYPE(x)  ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)      ((x) << 0x07) // Present
#define SEG_SAVL(x)      ((x) << 0x0C) // Available for system use
#define SEG_LONG(x)      ((x) << 0x0D) // Long mode
#define SEG_SIZE(x)      ((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)      ((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)     (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)
 
#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed
 
#define GDT_CODE_PL0	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
			SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
			SEG_PRIV(0)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL0	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
			SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
			SEG_PRIV(0)     | SEG_DATA_RDWR

#define GDT_STACK_PL0	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
			SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
			SEG_PRIV(0)     | SEG_DATA_RDWREXPD
 
#define GDT_CODE_PL3	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
			SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
			SEG_PRIV(3)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL3	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
			SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
			SEG_PRIV(3)     | SEG_DATA_RDWR

#define GDT_STACK_PL3	SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
			SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
			SEG_PRIV(3)     | SEG_DATA_RDWREXPD

#define GDT_ADDRESS	0x00000800
#define MULTI_ADDRESS    0x000007B0 
#define STRING_ADDRESS	0x000007D0 
#define GDT_ENTRIES	7
#define FLAG_D_32	0xCF


/* ************************************************************************** */
/* 			Structs                                               */
/* ************************************************************************** */

typedef struct  __attribute__((packed)) gdt_entry
{
	uint16_t limit_low;		// The lower 16 bits of the limit.
	uint16_t base_low;		// The lower 16 bits of the base.
	uint8_t  base_middle;		// The next 8 bits of the base.
	uint8_t  access;		// Access flags, determine what ring this segment can be used in.
	uint8_t  attributes;
	uint8_t  base_high;		// The last 8 bits of the base.
} 	t_gdt_entry;

typedef struct  __attribute__((packed)) gdt_ptr
{
	uint16_t limit;			// The upper 16 bits of all selector limits.
	uint32_t base;			// The address of the first gdt_entry_t struct.
}	t_gdt_ptr;



enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};


/* ************************************************************************** */
/*				Global                                        */
/* ************************************************************************** */

/* ************************************************************************** */
/*				Prototype                                     */
/* ************************************************************************** */


extern void load_gdt(uint32_t gdt_ptr);

extern t_gdt_entry	gdt_entries[GDT_ENTRIES];
extern t_gdt_ptr	*gdt_ptr;

void	init_gdt();
//void	hexdump(void *mem_addr, uint32_t size);
void	ft_putstr(const char* str);


void	terminal_initialize();
void	kernel_main(void); 

void	ft_putchar(char c );
void	terminal_writechar(char c, char colour);


//void	hex_to_str(unsigned int addr, char *result);

char	*itoa_base(int num, int base);
void	*kmemcpy(void *dest, const void *src, size_t n);
void	ft_putstr_color(const char* str, uint32_t color);
void	copyFunction(void *srcFunction, void *destFunction, size_t size);
void	print_register();
void	set_function();
void	set_string();

void				read_to_stack(void *mem_addr, uint32_t size);

#endif
