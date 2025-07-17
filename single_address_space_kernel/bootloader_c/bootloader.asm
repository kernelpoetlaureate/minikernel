BITS 16
ORG 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov si, msg
    call print_string

    hlt

print_string:
    mov ah, 0x0E
.next_char:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .next_char
.done:
    ret

msg db "Bootloader loaded!", 0

times 510-($-$$) db 0
DW 0xAA55

copy /b build\\bootloader.bin+build\\kernel.o build\\os_image.bin
