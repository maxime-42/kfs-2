bits 32
section .multiboot
	dd 0x1BADB002	; Magic number
	dd 0x0			; Flags
	dd - (0x1BADB002 + 0x0)	; Checksum

extern kmain

global load_gdt
global _start


load_gdt:
	mov eax, [esp + 4]
	lgdt [eax]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov ss, ax
  
	mov ax, 0x18
	mov gs, ax

	jmp 0x08:.flush
.flush:
	ret


_start:
	mov esp, stack_space        	; set stack pointer
	cli				; Disable interrupts
	mov esp, stack_space
	call kmain
	hlt

section .bss
resb 8192			; 8KB for stack
stack_space:

