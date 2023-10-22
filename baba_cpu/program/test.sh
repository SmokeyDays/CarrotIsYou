./clang --target=riscv32-unknown-unknown -march=rv32im -ffreestanding -fno-builtin -nostdlib -mno-relax -fno-PIE -G=0 -DRISCV -fno-rtti -fno-exceptions -T ~/test/tetris/rv_linker.lds -o ./build/mgt ~/test/tetris/src/*.c
./objcopy ./build/mgt --dump-section .text=./build/rom.bin --dump-section .data=./build/ram.bin
od -w4 -An --endian little -v -t x4 ./build/rom.bin > ./build/rom.mem
od -w4 -An --endian little -v -t x4 ./build/ram.bin > ./build/ram.mem

./clang -T ~/test/tetris/rv_linker.lds --target=riscv32-unknown-unknown ~/test/tetris/src/*.c -march=rv32im -ffreestanding -fno-builtin -nostdlib  -mno-relax -fno-PIE -G=0 -o ./build/mgt