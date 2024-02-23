GREY        =   \033[030m
RED         =   \033[031m
GREEN       =   \033[032m
YELLOW      =   \033[033m
BLUE        =   \033[034m
MAGENTA     =   \033[035m
CYAN        =   \033[036m
BOLD        =   \033[1m
RESET       =   \033[0m

TARGET      = myos
ISO         = $(TARGET).iso
KERNEL_OUT  = myos.bin

FLAGS       = -Wall -Wextra -Werror -fno-builtin -nostdlib -nodefaultlibs

GRUB_CFG    = grub.cfg
BOOT        = boot.s
SRC         = kernel.c libk.c gdt.c
LINKER      = linker.ld
OBJ         = boot.o kernel.o libk.o gdt.o

# **************************************************************************** #
# 📖 RULES
# **************************************************************************** #

all: build

build: fclean
	@nasm -f elf32 ${BOOT} -o boot.o
	@gcc -m32 -ffreestanding ${FLAGS} -c ${SRC}
	@printf "$(BOLD)$(GREEN)[✓] KERNEL BUILD DONE$(RESET)"
	@ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} ${OBJ}
	@printf "$(BOLD)$(GREEN)[✓] KERNEL LINK DONE$(RESET)"
	@make verify-multiboot
	@make build-iso

verify-multiboot:
	@if grub-file --is-x86-multiboot ${KERNEL_OUT}; then \
        printf "$(BOLD)$(GREEN)[✓] Multiboot header is valid$(RESET)"; \
    else \
        printf "$(BOLD)$(RED)[✗] Multiboot header is not valid$(RESET)"; \
        exit 1; \
    fi

build-iso:
	@mkdir -p isodir/boot/grub
	@cp ${KERNEL_OUT} isodir/boot/${TARGET}.bin
	@cp ${GRUB_CFG} isodir/boot/grub/grub.cfg
	@grub-mkrescue /usr/lib/grub/i386-pc -o myos.iso isodir
	@printf "$(BOLD)$(GREEN)[✓] ISO BUILD DONE$(RESET)"

clean:
	@rm -rf $(KERNEL_OUT) *.o $(ISO)
	@printf "$(BOLD)$(RED)[♻︎] DELETE KERNEL DONE$(RESET)"

fclean: clean
	@rm -rf isodir ${ISO}
	@clear
	@printf "$(BOLD)$(RED)[♻︎] DELETE BUILD/ DONE$(RESET)"

qemu:
	@qemu-system-i386 -cdrom ${ISO}

qemu-no-iso:
	@qemu-system-i386 -kernel ${KERNEL_OUT}

