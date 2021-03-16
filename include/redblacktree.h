#ifndef _REDBLACKTREE_H
#define	_REDBLACKTREE_H
#ifndef _STDDEF_H
#define offsetof(TYPE,MEMBER)	(((size_t)&((TYPE*)0)->MEMBER))
#endif
#define containerof(ptr,type,member)	({	\
		const typeof(((type*)0)->member) *m_ptr=ptr;\
		(type*)((char*)m_ptr-offsetof(type,member));})
#define rb_entry(ptr,type,member)	containerof(ptr,type,member)
enum rb_color{
	black,
	red
};
typedef struct rb_header rb_header_DEF;
struct rb_header{
	struct rb_header* left;
	struct rb_header* right;
	struct rb_header* parent;
	enum rb_color color;
};
struct rb_tree{
	struct rb_header* root;
};




#endif
