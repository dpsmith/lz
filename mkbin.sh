#! /bin/sh
#
# Copyright (c) 2019 Oracle and/or its affiliates. All rights reserved.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

cp -f lz_header lz_header.elf

objcopy --remove-section .data lz_header
objcopy --remove-section .data.rel.local lz_header
objcopy --remove-section .interp lz_header
objcopy --remove-section .dynsym lz_header
objcopy --remove-section .dynstr lz_header
objcopy --remove-section .hash lz_header
objcopy --remove-section .eh_frame lz_header
objcopy --remove-section .rela.dyn lz_header
objcopy --remove-section .dynamic lz_header
objcopy --remove-section .got.plt lz_header
objcopy --remove-section .signature lz_header
objcopy --remove-section .comment lz_header
objcopy --remove-section .symtab lz_header
objcopy --remove-section .strtab lz_header
objcopy --remove-section .shstrtab lz_header

# Make flat binary image
objcopy -O binary --pad-to 0x10000 lz_header lz_header.bin

# Plus some debug files
objdump -d lz_header.elf > lz_header.dsm
hexdump -C lz_header.bin > lz_header.hex
