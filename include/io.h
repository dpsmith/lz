/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author H. Peter Anvin
 *
 *   This file is part of the Linux kernel, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

/*
 * Header file for the real-mode kernel code
 */

/*
 * Just a snippet from kernel of what we need
 */

#include <defs.h>
#include <types.h>

#ifndef __IO_H__
#define __IO_H__

/* Fences */
#define mb()		asm volatile("mfence" : : : "memory")
#define rmb()		asm volatile("lfence" : : : "memory")
#define wmb()		asm volatile("sfence" : : : "memory")
#define barrier()	asm volatile("" : : : "memory")

/* MMIO Functions */
static inline u8 ioread8(void *addr)
{
	u8 val;

	barrier();
	val = (*(volatile u8 *)(addr));
	rmb();
	return val;
}

static inline u16 ioread16(void *addr)
{
	u16 val;

	barrier();
	val = (*(volatile u16 *)(addr));
	rmb();
	return val;
}

static inline u32 ioread32(void *addr)
{
	u32 val;

	barrier();
	val = (*(volatile u32 *)(addr));
	rmb();
	return val;
}

static inline void iowrite8(void *addr, u8 val)
{

	wmb();
	(*(volatile u8 *)(addr)) = val;
	barrier();
}

static inline void iowrite16(void *addr, u16 val)
{

	wmb();
	(*(volatile u16 *)(addr)) = val;
	barrier();
}

static inline void iowrite32(void *addr, u32 val)
{
	wmb();
	(*(volatile u32 *)(addr)) = val;
	barrier();
}

/* Basic port I/O */
static inline u8 inb(u16 port)
{
	u8 val;

	asm volatile("inb %1,%0" : "=a" (val) : "dN" (port));
	return val;
}

static inline u16 inw(u16 port)
{
	u16 val;

	asm volatile("inw %1,%0" : "=a" (val) : "dN" (port));
	return val;
}

static inline u32 inl(u16 port)
{
	u32 val;

	asm volatile("inl %1,%0" : "=a" (val) : "dN" (port));
	return val;
}

static inline void outb(u16 port, u8 val)
{
	asm volatile("outb %0,%1" : : "a" (val), "dN" (port));
}

static inline void outw(u16 port, u16 val)
{
	asm volatile("outw %0,%1" : : "a" (val), "dN" (port));
}

static inline void outl(u16 port, u32 val)
{
	asm volatile("outl %0,%1" : : "a" (val), "dN" (port));
}

static inline void io_delay(void)
{
	const u16 DELAY_PORT = 0x80;

	asm volatile("outb %%al,%0" : : "dN" (DELAY_PORT));
}

static inline void die(void)
{
	asm volatile("ud2");
}

#endif /* __IO_H__ */
