#!/bin/sh

qemu-system-arm -M raspi2 -nographic -monitor null -serial null -semihosting -kernel "$@"
