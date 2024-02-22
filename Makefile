GREY    	=	\033[030m
RED     	=	\033[031m
GREEN   	=	\033[032m
YELLOW  	=	\033[033m
BLUE    	=	\033[034m
MAGENTA 	=	\033[035m
CYAN		=	\033[036m
BOLD		=	\033[1m
RESET   	=	\033[0m

TARGET		= myos

ISO		= $(TARGET).iso

KERNEL_OUT = myos.bin


FLAGS		= -Wall -Wextra -Werror -fno-builtin -fno-builtin -fno-builtin -nostdlib -nodefaultlibs

GRUB_CFG 	= grub.cfg

BOOT		= boot.s

SRC		= kernel.c libk.c gdt.c  

LINKER		= linker.ld

OBJ		= boot.o kernel.o libk.o gdt.o  

# **************************************************************************** #
# 📖 RULES
# **************************************************************************** #

all: build

build: fclean
	@nasm -f elf32 ${BOOT} -o boot.o
	@gcc -m32 -ffreestanding ${FLAGS} -c ${SRC}
	@echo "$(BOLD)$(GREEN)[✓] KERNEL BUILD DONE$(RESET)"
	@ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} ${OBJ}
	@echo "$(BOLD)$(GREEN)[✓] KERNEL LINK DONE$(RESET)"




clean:
	@rm -rf $(KERNEL_OUT)  *.o
	@echo "$(BOLD)$(RED)[♻︎] DELETE KERNEL DONE$(RESET)"

fclean: clean
	clear
	@echo "$(BOLD)$(RED)[♻︎] DELETE BUILD/ DONE$(RESET)"
