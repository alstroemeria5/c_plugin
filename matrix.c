#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "matrix.h"
#include "dll.h"

int matrix_global_error_descriptor=0;
char *matrix_global_error[]={
							"Nothing wrong yet!!!",
							"no matrix at all!",
							"matrix multiplication first and second not match!"
							"matrix comparison dimension not match!"};
DLL_PUBLIC bool two_d_Matrix_comparison(two_d_Matrix_DEF* a,two_d_Matrix_DEF* b)
{
	if(a==NULL||b==NULL){
			matrix_global_error_descriptor=matrix_NULL; 																/*Left to future debug print*/
			return false;
		}
	if((a->row!=b->row)||(a->column!=b->column)){
		matrix_global_error_descriptor=matrix_comparison_dimension_not_match;
		return false;
	}
	int row=a->row;
	int column=b->column;
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(a->ptr_to_matrix[i][j]!=b->ptr_to_matrix[i][j]){
				return false;
			}
		}
	}
	return true;
}
DLL_LOCAL two_d_Matrix_DEF* two_d_Matrix_transpose(two_d_Matrix_DEF* ptr_two_d_Matrix)
{
	int row=ptr_two_d_Matrix->column;
	int column=ptr_two_d_Matrix->row;
	two_d_Matrix_DEF* matrix_transpose=two_d_Matrix_alloc_init(row,column);
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			matrix_transpose->ptr_to_matrix[i][j]=ptr_two_d_Matrix->ptr_to_matrix[j][i];
		}
	}
	return matrix_transpose;
}
DLL_PUBLIC two_d_Matrix_DEF* two_d_Matrix_multiply(two_d_Matrix_DEF* ptr_two_d_Matrix_one,two_d_Matrix_DEF* ptr_two_d_Matrix_two)
{
	if(ptr_two_d_Matrix_one==NULL||ptr_two_d_Matrix_two==NULL){
		matrix_global_error_descriptor=matrix_NULL;																	/*Left to future debug print*/
		return NULL;
	}
	if(ptr_two_d_Matrix_one->column!=ptr_two_d_Matrix_two->row){
		matrix_global_error_descriptor=matrix_mutiplicaion_dimension_not_match;
		return NULL;
	}
	two_d_Matrix_DEF* two_d_Matrix_answer=two_d_Matrix_alloc_init(ptr_two_d_Matrix_one->row,ptr_two_d_Matrix_two->column);
	int temp;
	int size=ptr_two_d_Matrix_one->column;
	int row=ptr_two_d_Matrix_one->row;
	int column=ptr_two_d_Matrix_two->column;
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			temp=0;
			for(int k=0;k<size;k++){
				temp+=ptr_two_d_Matrix_one->ptr_to_matrix[i][k]*ptr_two_d_Matrix_two->ptr_to_matrix[k][j];
			}
			two_d_Matrix_answer->ptr_to_matrix[i][j]=temp;
		}
	}
	return two_d_Matrix_answer;
}
DLL_PUBLIC void two_d_Matrix_cpy(two_d_Matrix_DEF* two_d_Matrix_dst,two_d_Matrix_DEF* two_d_Matrix_src)
{
	if((two_d_Matrix_dst->row!=two_d_Matrix_src->row)||(two_d_Matrix_dst->column!=two_d_Matrix_src->column)){
		matrix_global_error_descriptor=matrix_copy_dimension_not_match;
		return;
	}
	int row=two_d_Matrix_dst->row;
	int column=two_d_Matrix_dst->column;
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			two_d_Matrix_dst->ptr_to_matrix[i][j]=two_d_Matrix_src->ptr_to_matrix[i][j];
		}
	}
	return;
}
DLL_PUBLIC void two_d_Matrix_cpy_c_array(two_d_Matrix_DEF* two_d_Matrix_dst,int row_size,int array_pointer[][row_size])
{
	int row=two_d_Matrix_dst->row;
	int column=two_d_Matrix_dst->column;
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			two_d_Matrix_dst->ptr_to_matrix[i][j]=array_pointer[i][j];
		}
	}
	return;
}	
DLL_PUBLIC two_d_Matrix_DEF* two_d_Matrix_alloc_init(int row,int column)
{
	two_d_Matrix_DEF* ptr_Matrix=malloc(sizeof(two_d_Matrix_DEF));
	ptr_Matrix->ptr_to_matrix=two_dimension_matrix_alloc_init(row,column);
	ptr_Matrix->row=row;
	ptr_Matrix->column=column;
	return ptr_Matrix;
}
DLL_PUBLIC void two_d_Matrix_free(two_d_Matrix_DEF** ptr_two_d_Matrix)
{	
	assert((ptr_two_d_Matrix!=NULL)&&(*ptr_two_d_Matrix!=NULL));
	if((*ptr_two_d_Matrix)->ptr_to_matrix){
		two_dimension_matrix_free(&((*ptr_two_d_Matrix)->ptr_to_matrix),(*ptr_two_d_Matrix)->row);
	}
	free(*ptr_two_d_Matrix);
	*ptr_two_d_Matrix=NULL;
	return;
}
DLL_PUBLIC void two_d_Matrix_set_number(two_d_Matrix_DEF* ptr_two_d_Matrix,int i,int j,int assign){
			ptr_two_d_Matrix->ptr_to_matrix[i][j]=assign;
			return;
}
DLL_PUBLIC void two_d_Matrix_print(two_d_Matrix_DEF* ptr_two_d_mat)
{
	assert((ptr_two_d_mat!=NULL)&&(ptr_two_d_mat->ptr_to_matrix!=NULL));
	int row=ptr_two_d_mat->row;
	int column=ptr_two_d_mat->column;
	matrix_debug(stdout,"Matrix element%s:\n","");
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			printf("%d ",ptr_two_d_mat->ptr_to_matrix[i][j]);
		}
		printf("\n");
	}
	return;
}
DLL_LOCAL int** two_dimension_matrix_alloc_init(int row,int column)
{
	int** ptr_to_row=malloc(sizeof(int*)*row);
	for(int i=0;i<row;i++){
		ptr_to_row[i]=malloc(sizeof(int)*column);
	}
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			ptr_to_row[i][j]=0;
		}
	}
	return ptr_to_row;
}
DLL_LOCAL void two_dimension_matrix_free(int*** ptr_to_row,int row)
{
	assert((ptr_to_row!=NULL)&&(*ptr_to_row!=NULL));
	for(int i=0;i<row;i++){
		if((*ptr_to_row)[i]){
			free((*ptr_to_row)[i]);
		}
		else{
			;
		}
	}
	free(*ptr_to_row);
	*ptr_to_row=NULL;
	return;
}


