

#ifndef _PLUGIN_RB_H
#define _PLUGIN_RB_H

#ifndef _PLUGIN_H
#include "plugin.h"
#endif

#ifndef _REDBLACKTREE_H
#include "redblacktree.h"
#endif
typedef struct plugin_rb_tree plugin_rb_tree_DEF;
typedef struct plugin_rb_node plugin_rb_node_DEF;
#define ptr_rb_header(plugin_rb_node_t)	&plugin_rb_node_t->rb_header
#define rb_header(plugin_rb_node_t)	plugin_rb_node_t->rb_header
struct plugin_rb_tree{
	rb_header_DEF* root;
	rb_header_DEF* nil_ptr;
};
struct plugin_rb_node{
	rb_header_DEF rb_header;
	plugin_DEF*	ptr_plugin;
};
/*function declaration*/
#ifdef __cplusplus
extern "c" {
#endif
extern void plugin_rb_tree_node_insert(plugin_rb_tree_DEF* ptr_rb_tree,plugin_DEF* ptr_plugin);
extern plugin_rb_tree_DEF*	plugin_rb_tree_alloc_init();
extern void plugin_rb_tree_free(plugin_rb_tree_DEF** ptr_rb_tree);
extern void __plugin_rb_tree_postorder_delete_all_node(rb_header_DEF* ptr_rb_header,rb_header_DEF* nil_ptr);
extern void plugin_rb_tree_replace_plugin_rb_linked_list_inorder(plugin_rb_tree_DEF* ptr_rb_tree,plugin_linked_list_DEF* ptr_plugin_list);
extern void __plugin_rb_tree_replace_plugin_rb_linked_list_inorder(rb_header_DEF* ptr_rb_node,rb_header_DEF* nil_ptr,plugin_linked_list_DEF* ptr_plugin_list);


extern plugin_rb_node_DEF* plugin_rb_node_alloc_init(plugin_DEF* ptr_plugin,rb_header_DEF* left,rb_header_DEF* right,rb_header_DEF* parent);
extern void plugin_rb_tree_inorder_traversal(plugin_rb_tree_DEF* ptr_plugin_rb_tree);
extern void __plugin_rb_tree_inorder_traversal(rb_header_DEF* ptr_rb_node,rb_header_DEF* nil_ptr);

extern void __rb_header_insert_fix_RBT(rb_header_DEF* current,rb_header_DEF* root,rb_header_DEF* nil_ptr);
extern void __rb_header_LeftRotation(rb_header_DEF* x,rb_header_DEF* root,rb_header_DEF* nil_ptr);
extern void __rb_header_RightRotation(rb_header_DEF* x,rb_header_DEF* root,rb_header_DEF* nil_ptr);
#ifdef __cplusplus
{
#endif

#endif


	
