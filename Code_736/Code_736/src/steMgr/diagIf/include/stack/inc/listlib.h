/**************************************************************************
 * FILE PURPOSE	:  	Header file for the linked list library.
 **************************************************************************
 * FILE NAME	:   listlib.h
 *
 * DESCRIPTION	:
 * 	Contains structures and exported function that are used by the linked
 * 	list library.
 *
 *	(C) Copyright 2002, Texas Instruments, Inc.
 *************************************************************************/

#ifndef __LISTLIB_H__
#define __LISTLIB_H__

/**************************************************************************
 * STRUCTURE -  LIST_NODE
 **************************************************************************
 *	The structure defines a LIST NODE structure that contains links to the 
 *	previous and next element in the list.
 **************************************************************************/
typedef struct LIST_NODE
{
	void*	p_next;		/* Pointer to the next element in the list. 	*/	
    void*   p_prev;     /* Pointer to the prev element in the list. */
}LIST_NODE;

/************************ EXTERN Functions *********************************/

_extern void list_add (LIST_NODE **ptr_list, LIST_NODE *ptr_node);
_extern LIST_NODE* list_remove (LIST_NODE **ptr_list);
_extern LIST_NODE* list_get_head (LIST_NODE **ptr_list);
_extern LIST_NODE* list_get_next (LIST_NODE *ptr_list);
_extern int list_remove_node (LIST_NODE **ptr_list, LIST_NODE *ptr_remove);
_extern void list_cat (LIST_NODE **ptr_dst, LIST_NODE **ptr_src);
_extern LIST_NODE* list_replicate (LIST_NODE* ptr_srcList, int size, void* alloc(UINT32 size), void free (void *ptr));
_extern void list_clean (LIST_NODE* ptr_list, void free (void *ptr));

#endif	/* __LISTLIB_H__ */



