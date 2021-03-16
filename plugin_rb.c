#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "plugin.h"
#include "plugin_rb.h"
#include "dll.h"
DLL_PUBLIC void plugin_rb_tree_node_insert(plugin_rb_tree_DEF* ptr_rb_tree,plugin_DEF* ptr_plugin)
{
	assert((ptr_rb_tree!=NULL)&&(ptr_plugin!=NULL)&&(ptr_rb_tree->nil_ptr!=NULL));
	rb_header_DEF* nil_ptr=ptr_rb_tree->nil_ptr;
	if(ptr_rb_tree->root==ptr_rb_tree->nil_ptr){
		plugin_rb_node_DEF* ptr_temp=plugin_rb_node_alloc_init(ptr_plugin,nil_ptr,nil_ptr,nil_ptr);
		ptr_rb_tree->root=&ptr_temp->rb_header;
		return;
	}
	rb_header_DEF** ptr_temp=&ptr_rb_tree->root;
	while(1){
		if(*ptr_temp==nil_ptr){
			*ptr_temp=&plugin_rb_node_alloc_init(ptr_plugin,nil_ptr,nil_ptr,nil_ptr)->rb_header;
			break;
		}	
		if(ptr_plugin->static_order<=rb_entry(*ptr_temp,plugin_rb_node_DEF,rb_header)->ptr_plugin->static_order){
			ptr_temp=&((*ptr_temp)->left);
		}
		else{
			ptr_temp=&((*ptr_temp)->right);
		}
	}
	__rb_header_insert_fix_RBT(*ptr_temp,&ptr_rb_tree->root,nil_ptr);
	return;
}
DLL_PUBLIC void plugin_rb_tree_inorder_traversal(plugin_rb_tree_DEF* ptr_plugin_rb_tree)
{
	assert(ptr_plugin_rb_tree);
	if(ptr_plugin_rb_tree->root==ptr_plugin_rb_tree->nil_ptr){
		return;
	}
	__plugin_rb_tree_inorder_traversal(ptr_plugin_rb_tree->root,ptr_plugin_rb_tree->nil_ptr);
	
}	
DLL_LOCAL void __plugin_rb_tree_inorder_traversal(rb_header_DEF* ptr_rb_node,rb_header_DEF* nil_ptr)
{
	assert((ptr_rb_node!=NULL)&&(nil_ptr!=NULL));
	if(ptr_rb_node!=nil_ptr){
		__plugin_rb_tree_inorder_traversal(ptr_rb_node->left,nil_ptr);
		plugin_debug(stdout,"library name:%s\n",rb_entry(ptr_rb_node,plugin_rb_node_DEF,rb_header)->ptr_plugin->name);
		__plugin_rb_tree_inorder_traversal(ptr_rb_node->right,nil_ptr);
		return;
	}
	else{
		return;
	}
}
DLL_PUBLIC plugin_rb_node_DEF* plugin_rb_node_alloc_init(plugin_DEF* ptr_plugin,rb_header_DEF* left,rb_header_DEF* right,rb_header_DEF* parent)
{
	plugin_rb_node_DEF* ptr_plugin_rb_node=malloc(sizeof(plugin_rb_node_DEF));
	ptr_plugin_rb_node->rb_header.left=left;
	ptr_plugin_rb_node->rb_header.right=right;
	ptr_plugin_rb_node->rb_header.parent=parent;
	ptr_plugin_rb_node->ptr_plugin=ptr_plugin;
}
DLL_PUBLIC plugin_rb_tree_DEF*	plugin_rb_tree_alloc_init()
{
	plugin_rb_tree_DEF* ptr_rb_tree=malloc(sizeof(plugin_rb_tree_DEF));
	ptr_rb_tree->nil_ptr=malloc(sizeof(rb_header_DEF));
	ptr_rb_tree->nil_ptr->color=black;
	ptr_rb_tree->nil_ptr->parent=ptr_rb_tree->nil_ptr;
	ptr_rb_tree->nil_ptr->left=ptr_rb_tree->nil_ptr;
	ptr_rb_tree->nil_ptr->right=ptr_rb_tree->nil_ptr;
	ptr_rb_tree->root=ptr_rb_tree->nil_ptr;
	return ptr_rb_tree;
}
DLL_PUBLIC void plugin_rb_tree_free(plugin_rb_tree_DEF** ptr_rb_tree)
{
	assert((ptr_rb_tree!=NULL)&&(*ptr_rb_tree!=NULL));
	rb_header_DEF* root=(*ptr_rb_tree)->root;
	if(root==(*ptr_rb_tree)->nil_ptr){
		free((*ptr_rb_tree)->nil_ptr);
		free(*ptr_rb_tree);
		*ptr_rb_tree=NULL;
		return;
	}
	__plugin_rb_tree_postorder_delete_all_node(root,(*ptr_rb_tree)->nil_ptr);
	free((*ptr_rb_tree)->nil_ptr);
	free(*ptr_rb_tree);
	*ptr_rb_tree=NULL;
	return;
}
DLL_LOCAL void __plugin_rb_tree_postorder_delete_all_node(rb_header_DEF* ptr_rb_header,rb_header_DEF* nil_ptr)
{
	if(ptr_rb_header==nil_ptr){
		return;
	}
	__plugin_rb_tree_postorder_delete_all_node(ptr_rb_header->left,nil_ptr);
	__plugin_rb_tree_postorder_delete_all_node(ptr_rb_header->right,nil_ptr);
	free(rb_entry(ptr_rb_header,plugin_rb_node_DEF,rb_header));
}
DLL_PUBLIC void plugin_rb_tree_replace_plugin_rb_linked_list_inorder(plugin_rb_tree_DEF* ptr_rb_tree,plugin_linked_list_DEF* ptr_plugin_list)
{
	assert((ptr_rb_tree!=NULL)&&(ptr_plugin_list!=NULL));
	if(ptr_rb_tree->root==ptr_rb_tree->nil_ptr){
		return;
	}
	plugin_linked_list_nullify(ptr_plugin_list);
	__plugin_rb_tree_replace_plugin_rb_linked_list_inorder(ptr_rb_tree->root,ptr_rb_tree->nil_ptr,ptr_plugin_list);
}
DLL_LOCAL void __plugin_rb_tree_replace_plugin_rb_linked_list_inorder(rb_header_DEF* ptr_rb_node,rb_header_DEF* nil_ptr,plugin_linked_list_DEF* ptr_plugin_list)
{
	if(ptr_rb_node!=nil_ptr){
		__plugin_rb_tree_replace_plugin_rb_linked_list_inorder(ptr_rb_node->left,nil_ptr,ptr_plugin_list);
		plugin_node_insert_to_list(rb_entry(rb_entry(ptr_rb_node,plugin_rb_node_DEF,rb_header)->ptr_plugin,plugin_node_DEF,plugin),ptr_plugin_list);
		__plugin_rb_tree_replace_plugin_rb_linked_list_inorder(ptr_rb_node->right,nil_ptr,ptr_plugin_list);
	}
}
DLL_LOCAL void __rb_header_insert_fix_RBT(rb_header_DEF* current,rb_header_DEF** root,rb_header_DEF* nil_ptr)
{
	 
    while (current->parent->color==red) {   
        if (current->parent == current->parent->parent->left) { 
            rb_header_DEF* uncle = current->parent->parent->right;
            if (uncle->color == red) {
                current->parent->color = black;
                uncle->color = black;
                current->parent->parent->color = red;              
                current = current->parent->parent;
            }
            else {  
                if (current == current->parent->right){    
                    current = current->parent;
                    __rb_header_LeftRotation(current,root,nil_ptr);
                }
                current->parent->color = black;                   
                current->parent->parent->color = red;           
                __rb_header_RightRotation(current->parent->parent,root,nil_ptr);
            }
        }
      
        else {  
            rb_header_DEF *uncle = current->parent->parent->left;
            if (uncle->color == red) {
                current->parent->color = black;
                uncle->color = black;
                current->parent->parent->color = red;             
                current = current->parent->parent;
            }
            
            else {
                if (current == current->parent->left) {     
                    current = current->parent;
                    __rb_header_RightRotation(current,root,nil_ptr);
                }
                
                current->parent->color = black;
                current->parent->parent->color = red;
                __rb_header_LeftRotation(current->parent->parent,root,nil_ptr);
            }
        }
    }
    (*root)->color = black;
}
DLL_LOCAL void __rb_header_LeftRotation(rb_header_DEF* x,rb_header_DEF** root,rb_header_DEF* nil_ptr)
{
 	rb_header_DEF *y = x->right;         
    x->right = y->left;        
    if (y->left !=nil_ptr){           
        y->left->parent = x;       
    }
    y->parent = x->parent;               
    if (x->parent == nil_ptr){              
        *root = y;          
    }       
    else if (x == x->parent->left){ 
        x->parent->left = y;        
    }
    else{                                
        x->parent->right = y;       
    }
    y->left = x;                   
    x->parent = y;                       
}	
DLL_LOCAL void __rb_header_RightRotation(rb_header_DEF* x,rb_header_DEF** root,rb_header_DEF* nil_ptr)
{
 	rb_header_DEF *y = x->left;         
    x->left = y->right;        
    if (y->right != nil_ptr){           
        y->right->parent = x;       
    }
    y->parent = x->parent;               
    if (x->parent == nil_ptr){              
        *root = y;          
    }       
    else if (x == x->parent->left){ 
        x->parent->left = y;        
    }
    else{                                
        x->parent->right = y;       
    }
    y->right = x;                   
    x->parent = y;                       
}	
