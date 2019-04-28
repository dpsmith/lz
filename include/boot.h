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

/*
 * Header file for the real-mode kernel code
 */

#include <defs.h>
#include <types.h>

#ifndef __BOOT_H__
#define __BOOT_H__

typedef struct __packed sl_header {
	u16 lz_offet;
	u16 lz_length;
} sl_header_t;

typedef struct __packed lz_header {
	u8  uuid[16]; /* 78 f1 26 8e 04 92 11 e9  83 2a c8 5b 76 c4 cc 02 */
	u32 slaunch_loader_size;
	u32 zero_page_addr;
	u8  msb_key_hash[20];
} lz_header_t;

/* Assembly routines */
void load_stack(const void *new_stack);
void print_char(char c);
void stgi(void);
void lz_exit(const void *pm_enrty, const void *zp_base, const void *lz_base);

#endif /* __BOOT_H__ */
