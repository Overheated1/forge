nasm -f elf64 ./generated_code/generated_asm.asm -o ./build/generated_asm.o
ld ./build/generated_asm.o -o ./exe/generated_asm.exe
./exe/generated_asm.exe
echo $?