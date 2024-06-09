%macro mpl 2
mov rax, %2
imul %1    
mov  %1, rax
mov rax,60
%endmacro
%macro dvi 2
mov rax, %2
idiv %1    
mov  %1, rax
mov rax,60
%endmacro
section .data
section .text
global _start
  _start:
    mov rax,60
    add rdi,10
    add rdi,10
    add rdi,2
    syscall