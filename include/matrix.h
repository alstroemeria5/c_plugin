#ifndef _MATRIX_H
#define _MATRIX_H
#ifndef _STDLIB_H
#include <stdlib.h>
#endif
#ifndef __BOOLEAN__
#define __BOOLEAN__
#define bool int
#define true 1
#define false 0
#endif 
/*
#define matrix_ok	0
#define matrix_NULL	1
#define matrix_mutiplicaion_dimension_not_match	2
#define matrix_copy_dimension_not_match	3
*/
enum matrix_error_state{
	matrix_ok,
	matrix_NULL,
	matrix_mutiplicaion_dimension_not_match,
	matrix_copy_dimension_not_match,
	matrix_comparison_dimension_not_match
};
#define matrix_debug(filedescriptor,format,...) fprintf(filedescriptor,"[filename:%s,line:%d]		"format,__FILE__,__LINE__,__VA_ARGS__);
#define matrix_error()	matrix_debug(stderr,"%s\n",matrix_global_error[matrix_global_error_descriptor])
typedef struct two_d_Matrix two_d_Matrix_DEF;
struct two_d_Matrix{
	int** ptr_to_matrix;
	int row;
	int column;
};
extern int matrix_global_error_descriptor;
extern char *matrix_global_error[];
/*function declaration segment*/
#ifdef __cplusplus
extern "c" {
#endif

extern two_d_Matrix_DEF* two_d_Matrix_transpose(two_d_Matrix_DEF* ptr_two_d_Matrix);
extern bool two_d_Matrix_comparison(two_d_Matrix_DEF* a,two_d_Matrix_DEF* b);

extern two_d_Matrix_DEF* two_d_Matrix_multiply(two_d_Matrix_DEF* ptr_two_d_Matrix_one,two_d_Matrix_DEF* ptr_two_d_Matrix_two);
extern void two_d_Matrix_cpy(two_d_Matrix_DEF* two_d_Matrix_dst,two_d_Matrix_DEF* two_d_Matrix_src);
extern void two_d_Matrix_cpy_c_array(two_d_Matrix_DEF* two_d_Matrix_dst,int size,int array_pointer[][size]);

extern two_d_Matrix_DEF* two_d_Matrix_alloc_init(int row,int column);
extern void two_d_Matrix_free(two_d_Matrix_DEF** ptr_two_d_Matrix);


extern void two_d_Matrix_set_number(two_d_Matrix_DEF* ptr_two_d_Matrix,int i,int j,int assign);
extern void two_d_Matrix_print(two_d_Matrix_DEF* ptr_two_d_mat);

extern int** two_dimension_matrix_alloc_init(int row,int column);
extern void two_dimension_matrix_free(int*** ptr_to_row,int row);
#ifdef __cplusplus
{
#endif

#endif 
