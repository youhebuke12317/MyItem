/*
  Red Black Trees
  (C) 1999  Andrea Arcangeli <andrea@suse.de>
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  linux/include/linux/rbtree.h

  To use rbtrees you'll have to implement your own insert and search cores.
  This will avoid us to use callbacks and to drop drammatically performances.
  I know it's not the cleaner way,  but in C (not in C++) to get
  performances and genericity...

  See Documentation/rbtree.txt for documentation and samples.
*/

#ifndef	_LINUX_RBTREE_H
#define	_LINUX_RBTREE_H

#include <linux/kernel.h>
#include <linux/stddef.h>

/*
 * GCC支持很多属性，用来说明声明变量或函数的特殊性质
 *		__attribute__是关键字
 *		aligned指定了变量的对齐方式。
 * __attribute__((aligned(sizeof(long))))也就是要求对象要以long的长度对齐
 *
 * 其实 struct rb_node 结构中还包含了一个指向父结点的指针，那就是 __rb_parent_color 成员,
 * 它是 unsigned long 类型，因为在所有系统中，指针的长度总是和 long 型的长度相同，虽然C语
 * 言本身不要求这点，但事实确实如此。int 的长度就不一定了，在32位系统中int型也是32位，
 * 但在64位系统中，int型还是32位。
 *
 * 结点的颜色也包含在 __rb_parent_color 中，因为颜色只有黑或红，所以用1位就可以保存这个信
 * 息，那就是这个成员的最后一位。因为 struct rb_node 结构一定是按4或8对齐的，所以最后两位
 * 一定是0，所以用最后一位保存这个信息不会破坏指针的信息。红色用0表示，黑色用1表示：
 * */
struct rb_node {
	unsigned long  __rb_parent_color;
	struct rb_node *rb_right;
	struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long))));
    /* The alignment might seem pointless, but allegedly CRIS needs it */

struct rb_root {
	struct rb_node *rb_node;
};

// 为了获得指向父结点的指针，只需要把 __rb_parent_color 成员的最后两位还原成0即可
#define rb_parent(r)					((struct rb_node *)((r)->__rb_parent_color & ~3))

#define RB_ROOT							(struct rb_root) { NULL, }
#define	rb_entry(ptr, type, member)		container_of(ptr, type, member)

#define RB_EMPTY_ROOT(root)				((root)->rb_node == NULL)

/* 'empty' nodes are nodes that are known not to be inserted in an rbree */
#define RB_EMPTY_NODE(node)													\
	((node)->__rb_parent_color == (unsigned long)(node))
#define RB_CLEAR_NODE(node)													\
	((node)->__rb_parent_color = (unsigned long)(node))


extern void rb_insert_color(struct rb_node *, struct rb_root *);
extern void rb_erase(struct rb_node *, struct rb_root *);


/* Find logical next and previous nodes in a tree */
extern struct rb_node *rb_next(const struct rb_node *);
extern struct rb_node *rb_prev(const struct rb_node *);
extern struct rb_node *rb_first(const struct rb_root *);
extern struct rb_node *rb_last(const struct rb_root *);

/* Postorder iteration - always visit the parent after its children */
extern struct rb_node *rb_first_postorder(const struct rb_root *);
extern struct rb_node *rb_next_postorder(const struct rb_node *);

/* Fast replacement of a single node without remove/rebalance/add/rebalance */
extern void rb_replace_node(struct rb_node *victim, struct rb_node *new, 
			    struct rb_root *root);

static inline void rb_link_node(struct rb_node * node, struct rb_node * parent,
				struct rb_node ** rb_link)
{
	node->__rb_parent_color = (unsigned long)parent;
	node->rb_left = node->rb_right = NULL;

	*rb_link = node;
}

#define rb_entry_safe(ptr, type, member)									\
	({ typeof(ptr) ____ptr = (ptr);											\
	   ____ptr ? rb_entry(____ptr, type, member) : NULL;					\
	})

/**
 * rbtree_postorder_for_each_entry_safe - iterate over rb_root in post order of
 * given type safe against removal of rb_node entry
 *
 * @pos:	the 'type *' to use as a loop cursor.
 * @n:		another 'type *' to use as temporary storage
 * @root:	'rb_root *' of the rbtree.
 * @field:	the name of the rb_node field within 'type'.
 */
#define rbtree_postorder_for_each_entry_safe(pos, n, root, field)				\
	for (pos = rb_entry_safe(rb_first_postorder(root), typeof(*pos), field);	\
	     pos && ({ n = rb_entry_safe(rb_next_postorder(&pos->field),			\
			typeof(*pos), field); 1; });										\
	     pos = n)

#endif	/* _LINUX_RBTREE_H */
