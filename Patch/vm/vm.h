/*
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)vm.h	8.1 (Berkeley) 6/11/93
 */

#ifndef VM_H
#define VM_H

typedef int vm_inherit_t;		/* XXX: inheritance codes */

union vm_map_object;
typedef union vm_map_object vm_map_object_t;

struct vm_map_entry;
typedef struct vm_map_entry *vm_map_entry_t;

struct vm_map;
typedef struct vm_map *vm_map_t;

struct vm_object;
typedef struct vm_object *vm_object_t;

struct vm_page;
typedef struct vm_page  *vm_page_t;

struct pager_struct;
typedef struct pager_struct *vm_pager_t;

#include <sys/vmmeter.h>
#include <sys/queue.h>

/*
 * Compatibility with old MACH queue.h
 */
typedef struct queue_entry	*queue_t;
typedef	struct queue_entry	queue_head_t;
typedef	struct queue_entry	queue_chain_t;
typedef	struct queue_entry	*queue_entry_t;

#define	queue_first(head)	((head)->qe_next)
#define	queue_next(elm)		((elm)->qe_next)
#define	queue_empty(head)	((head)->qe_next == 0)
#define	queue_end(head, elm)	((elm) == 0)

#define queue_enter(head, elt, type, field) \
	queue_enter_tail(head, elt, type, field)

#define queue_remove_first(head, elt, type, field) { \
	elt = queue_first(head); \
	queue_remove(head, elt, type, field) \
}

#include <vm/vm_param.h>
#include <vm/lock.h>
#include <vm/vm_prot.h>
#include <vm/vm_inherit.h>
#include <vm/vm_map.h>
#include <vm/vm_object.h>
#include <vm/pmap.h>
#include <vm/vm_extern.h>

/*
 * Shareable process virtual address space.
 * May eventually be merged with vm_map.
 * Several fields are temporary (text, data stuff).
 */
struct vmspace {
	struct	vm_map vm_map;	/* VM address map */
	struct	pmap vm_pmap;	/* private physical map */
	int	vm_refcnt;	/* number of references */
	caddr_t	vm_shm;		/* SYS5 shared memory private data XXX */
/* we copy from vm_startcopy to the end of the structure on fork */
#define vm_startcopy vm_rssize
	segsz_t vm_rssize; 	/* current resident set size in pages */
	segsz_t vm_swrss;	/* resident set size before last swap */
	segsz_t vm_tsize;	/* text size (pages) XXX */
	segsz_t vm_dsize;	/* data size (pages) XXX */
	segsz_t vm_ssize;	/* stack size (pages) */
	caddr_t	vm_taddr;	/* user virtual address of text XXX */
	caddr_t	vm_daddr;	/* user virtual address of data XXX */
	caddr_t vm_maxsaddr;	/* user VA at max stack growth */
};
#endif /* VM_H */
