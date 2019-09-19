/*
 *   This file is a repaired version of the file "hand_d_tapenade_generated.c"
 *   Fixing list (all fixings are marked by the comment TFIX):
 *   
 * N    Wrong code                                                            Line      Fixed code                         
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 1)                                                                       =>(61)      #include "hand_d.h"
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 2)   typedef struct {         
 *          double* data;                                                   =>(62)
 *      } Matrix_diff;               
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 3)                                                                       =>(64-133)  ADDITIONAL FUNCTIONS
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 4)   int i;                                                              =>(639)     int i, j;
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 5)   *relativesd->data = 0.0;                                            =>(647)
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 6)   *base_relativesd->data = 0.0;                                       =>(655)     for (j = 0; j < base_relatives->nrows * base_relatives->ncols; j++)
 *                                                                                          base_relativesd[i].data[j] = 0.0;
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 7)   int i;                                                              =>(682)     int i, j;
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 8)   const Matrix_diff *base_relativesd;                                 =>(685)     Matrix_diff* base_relativesd = get_new_zero_matrix_diff_array(bone_count, base_relatives);
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 9)   *inverse_base_absolutesd->data = 0.0;                               =>(699)     for (j = 0; j < inverse_base_absolutes[i].nrows * inverse_base_absolutes[i].ncols; j++)
 *                                                                                          inverse_base_absolutesd[i].data[j] = 0.0;
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 10)  *base_positionsd->data = 0.0;                                       =>(714)     for (i = 0; i < base_positions->nrows * base_positions->ncols; i++)
 *                                                                                          base_positionsd->data[i] = 0.0;
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 11)                                                                      =>(743)     delete_matrix_diff_array(bone_count, base_relativesd);
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 12)  fill_nodiff(pose_params, 0.0);                                      =>(764)     fill_d(pose_params, pose_paramsd, 0.0);
 *      *pose_paramsd->data = 0.0;
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 13)  , Matrix_diff *base_positionsd, Matrix *weights, const Triangle *   =>(809)     , Matrix *weights, const Triangle
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    
 * 14)                                                                      =>(812)     Matrix_diff* base_positionsd = get_new_zero_matrix_diff(base_positions);
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 15)  Matrix_diff *inverse_base_absolutesd;                               =>(815)     Matrix_diff* inverse_base_absolutesd = get_new_zero_matrix_diff_array(bone_count, inverse_base_absolutes);
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 16)                                                                      =>(840)     delete_matrix_diff(base_positionsd);
 *                                                                                      delete_matrix_diff_array(bone_count, inverse_base_absolutesd);
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 17)  inverse_base_absolutes, Matrix *base_positions, Matrix_diff *       =>(856)     inverse_base_absolutes, Matrix *base_positions,
 *      base_positionsd, Matrix *weights, const Triangle *triangles, int                Matrix *weights, const Triangle *triangles, int
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 18)                                                                      =>(860)     Matrix_diff* base_positionsd = get_new_zero_matrix_diff(base_positions);
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 19)  Matrix_diff *inverse_base_absolutesd;                               =>(863)     Matrix_diff* inverse_base_absolutesd = get_new_zero_matrix_diff_array(bone_count, inverse_base_absolutes);
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 20)                                                                      =>(900)     delete_matrix_diff(base_positionsd);
 *                                                                                      delete_matrix_diff_array(bone_count, inverse_base_absolutesd);
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

/*        Generated by TAPENADE     (INRIA, Ecuador team)
    Tapenade 3.14 (r7259) - 18 Jan 2019 09:35
*/
#include "hand_d.h" /* TFIX */
                    /* TFIX */ // Matrix_diff declaration is moved to a header file

/*========================================================================*/
/*                          ADDITIONAL FUNCTIONS                          */
/*(added because of Tapenade can't recognize how initialize complex types)*/
/*========================================================================*/
// returns diff for the given matrix
Matrix_diff* get_new_zero_matrix_diff(const Matrix* mat) /* TFIX */
{
    Matrix_diff* result = (Matrix_diff*)malloc(sizeof(Matrix_diff));
    result->data = (double*)malloc(mat->nrows * mat->ncols * sizeof(double));

    for (int i = 0; i < mat->nrows * mat->ncols; i++)
    {
        result->data[i] = 0.0;
    }

    return result;
}



// removes matrix diff
void delete_matrix_diff(Matrix_diff* md) /* TFIX */
{
    if (md->data != NULL)
    {
        free(md->data);
    }

    free(md);
}



// creates new matrix diff array initialized by zeros
Matrix_diff* get_new_zero_matrix_diff_array(int count, const Matrix* m_arr) /* TFIX */
{
    Matrix_diff* result = (Matrix_diff*)malloc(count * sizeof(Matrix_diff));

    int i;
    for (i = 0; i < count; i++)
    {
        if (m_arr[i].data != NULL)
        {
            result[i].data = (double*)malloc(m_arr[i].nrows * m_arr[i].ncols * sizeof(double));
        }
        else
        {
            result[i].data = NULL;
        }
    }

    return result;
}



// delete matrix diff array
void delete_matrix_diff_array(int count, Matrix_diff* md_arr) /* TFIX */
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (md_arr[i].data != NULL)
        {
            free(md_arr[i].data);
        }
    }

    free(md_arr);
}





/*
  Differentiation of get_new_matrix in forward (tangent) mode:
   Plus diff mem management of: alloc(*mat).data:in-out get_new_matrix:in-out

========================================================================
                            MATRIX METHODS                              
========================================================================*/
// returns a new matrix of size nrows * ncols
Matrix_diff * get_new_matrix_d(int nrows, int ncols, Matrix **get_new_matrix) 
{
    Matrix *mat;
    Matrix_diff *matd;
    matd = (Matrix_diff *)malloc(sizeof(Matrix_diff));
    mat = (Matrix *)malloc(sizeof(Matrix));
    mat->nrows = nrows;
    mat->ncols = ncols;
    matd->data = (double *)malloc(nrows*ncols*sizeof(double));
    mat->data = (double *)malloc(nrows*ncols*sizeof(double));
    *get_new_matrix = mat;
    return matd;
}

/*
  Differentiation of get_new_empty_matrix in forward (tangent) mode:
   Plus diff mem management of: alloc(*mat).data:in-out get_new_empty_matrix:in-out
*/
// return new empty matrix
Matrix_diff * get_new_empty_matrix_d(Matrix **get_new_empty_matrix) {
    Matrix *mat;
    Matrix_diff *matd;
    matd = (Matrix_diff *)malloc(sizeof(Matrix_diff));
    mat = (Matrix *)malloc(sizeof(Matrix));
    mat->nrows = 0;
    mat->ncols = 0;
    mat->data = NULL;
    *get_new_empty_matrix = mat;
    return matd;
}

/*
  Differentiation of delete_matrix in forward (tangent) mode:
   Plus diff mem management of: mat:out *mat.data:out
*/
// disposes data matrix holds
void delete_matrix_d0(Matrix *mat, Matrix_diff *matd) {
    if (mat->data != NULL) {
        free(matd->data);
        free(mat->data);
    }
    free(matd);
    free(mat);
}

/*
  Differentiation of delete_matrix in forward (tangent) mode:
   variations   of useful results: *(*mat.data)
   with respect to varying inputs: *(*mat.data)
   Plus diff mem management of: mat:in-out *mat.data:in-out
*/
// disposes data matrix holds
void delete_matrix_d(Matrix *mat, Matrix_diff *matd) {
    if (mat->data != NULL) {
        free(matd->data);
        free(mat->data);
    }
    free(matd);
    free(mat);
}

/*
  Differentiation of get_matrix_array in forward (tangent) mode:
   Plus diff mem management of: get_matrix_array:in-out
*/
// creates array of matricies
Matrix_diff * get_matrix_array_d(int count, Matrix **get_matrix_array) {
    Matrix *result;
    Matrix_diff *resultd;
    resultd = (Matrix_diff *)malloc(count*sizeof(Matrix_diff));
    result = (Matrix *)malloc(count*sizeof(Matrix));
    int i;
    for (i = 0; i < count; ++i) {
        result[i].data = NULL;
        result[i].ncols = 0;
        result[i].nrows = result[i].ncols;
    }
    *get_matrix_array = result;
    return resultd;
}

/*
  Differentiation of delete_light_matrix_array in forward (tangent) mode:
   variations   of useful results: *(*matricies.data)
   with respect to varying inputs: *(*matricies.data)
   Plus diff mem management of: matricies:in-out *matricies.data:out
*/
// disposes array of matricies
void delete_light_matrix_array_d(Matrix *matricies, Matrix_diff *matriciesd, 
        int count) {
    int i;
    for (i = 0; i < count; ++i)
        if (matricies[i].data != NULL) {
            free(matriciesd[i].data);
            free(matricies[i].data);
        }
    free(matriciesd);
    free(matricies);
}

/*
  Differentiation of resize in forward (tangent) mode:
   Plus diff mem management of: *mat.data:in-out
*/
// sets a new size of a matrix
void resize_d0(Matrix *mat, Matrix_diff *matd, int nrows, int ncols) {
    if (mat->nrows*mat->ncols != nrows*ncols) {
        if (mat->data != NULL) {
            free(matd->data);
            free(mat->data);
        }
        if (nrows*ncols > 0) {
            matd->data = (double *)malloc(ncols*nrows*sizeof(double));
            mat->data = (double *)malloc(ncols*nrows*sizeof(double));
        } else
            mat->data = NULL;
    }
    mat->ncols = ncols;
    mat->nrows = nrows;
}

/*
  Differentiation of resize in forward (tangent) mode:
   variations   of useful results: *(*mat.data)
   with respect to varying inputs: *(*mat.data)
   Plus diff mem management of: mat:in *mat.data:in-out
*/
// sets a new size of a matrix
void resize_d(Matrix *mat, Matrix_diff *matd, int nrows, int ncols) {
    if (mat->nrows*mat->ncols != nrows*ncols) {
        if (mat->data != NULL) {
            free(matd->data);
            free(mat->data);
        }
        if (nrows*ncols > 0) {
            matd->data = (double *)malloc(ncols*nrows*sizeof(double));
            mat->data = (double *)malloc(ncols*nrows*sizeof(double));
        } else
            mat->data = NULL;
    }
    mat->ncols = ncols;
    mat->nrows = nrows;
}

/*
  Differentiation of mat_mult in forward (tangent) mode:
   variations   of useful results: alloc(*(*mat.data)) *(*out.data)
   with respect to varying inputs: alloc(*(*mat.data)) *(*out.data)
                *(*lhs.data) *(*rhs.data)
   Plus diff mem management of: out:in *out.data:in-out lhs:in
                *lhs.data:in rhs:in *rhs.data:in
*/
// multiplies matricies
void mat_mult_d(const Matrix *lhs, const Matrix_diff *lhsd, const Matrix *rhs,
        const Matrix_diff *rhsd, Matrix *out, Matrix_diff *outd) {
    int i, j, k;
    resize_d(out, outd, lhs->nrows, rhs->ncols);
    for (i = 0; i < lhs->nrows; ++i)
        for (k = 0; k < rhs->ncols; ++k) {
            outd->data[i + k*out->nrows] = lhsd->data[i+0*lhs->nrows]*rhs->
                data[0+k*rhs->nrows] + lhs->data[i+0*lhs->nrows]*rhsd->data[0+
                k*rhs->nrows];
            out->data[i + k*out->nrows] = lhs->data[i+0*lhs->nrows]*rhs->data[
                0+k*rhs->nrows];
            for (j = 1; j < lhs->ncols; ++j) {
                outd->data[i + k*out->nrows] = outd->data[i + k*out->nrows] + 
                    lhsd->data[i+j*lhs->nrows]*rhs->data[j+k*rhs->nrows] + lhs
                    ->data[i+j*lhs->nrows]*rhsd->data[j+k*rhs->nrows];
                out->data[i + k*out->nrows] += lhs->data[i+j*lhs->nrows]*rhs->
                data[j+k*rhs->nrows];
            }
        }
}

/*
  Differentiation of set_identity in forward (tangent) mode:
   variations   of useful results: *(*mat.data)
   with respect to varying inputs: *(*mat.data)
   Plus diff mem management of: mat:in *mat.data:in
*/
// set matrix identity
void set_identity_d(Matrix *mat, Matrix_diff *matd) {
    int i_col, i_row;
    for (i_col = 0; i_col < mat->ncols; ++i_col)
        for (i_row = 0; i_row < mat->nrows; ++i_row)
            if (i_col == i_row) {
                matd->data[i_row + i_col*mat->nrows] = 0.0;
                mat->data[i_row + i_col*mat->nrows] = 1.0;
            } else {
                matd->data[i_row + i_col*mat->nrows] = 0.0;
                mat->data[i_row + i_col*mat->nrows] = 0.0;
            }
}

/*
  Differentiation of fill in forward (tangent) mode:
   variations   of useful results: *(*mat.data)
   with respect to varying inputs: *(*mat.data)
   Plus diff mem management of: mat:in *mat.data:in
*/
// fills matrix with the given value
void fill_d(Matrix *mat, Matrix_diff *matd, double val) {
    int i;
    for (i = 0; i < mat->ncols*mat->nrows; ++i) {
        matd->data[i] = 0.0;
        mat->data[i] = val;
    }
}

// fills matrix with the given value
void fill_nodiff(Matrix *mat, double val) {
    int i;
    for (i = 0; i < mat->ncols*mat->nrows; ++i)
        mat->data[i] = val;
}

/*
  Differentiation of set_block in forward (tangent) mode:
   variations   of useful results: *(*mat.data)
   with respect to varying inputs: *(*block.data) *(*mat.data)
   Plus diff mem management of: block:in *block.data:in mat:in
                *mat.data:in
*/
// set a block of the matrix with another matrix
void set_block_d(Matrix *mat, Matrix_diff *matd, int row_off, int col_off, 
        const Matrix *block, const Matrix_diff *blockd) {
    int i_col, i_row;
    for (i_col = 0; i_col < block->ncols; ++i_col)
        for (i_row = 0; i_row < block->nrows; ++i_row) {
            matd->data[i_row + row_off + (i_col+col_off)*mat->nrows] = blockd
                ->data[i_row + i_col*block->nrows];
            mat->data[i_row + row_off + (i_col+col_off)*mat->nrows] = block->
                data[i_row + i_col*block->nrows];
        }
}

/*
  Differentiation of copy in forward (tangent) mode:
   variations   of useful results: alloc(*(*dst.data)) *(*dst.data)
   with respect to varying inputs: alloc(*(*dst.data)) *(*src.data)
                *(*dst.data)
   Plus diff mem management of: src:in *src.data:in dst:in *dst.data:in-out
*/
// copies one matrix to another
void copy_d(Matrix *dst, Matrix_diff *dstd, const Matrix *src, const 
        Matrix_diff *srcd) {
    int ii1;
    if (dst->data != NULL) {
        free(dstd->data);
        free(dst->data);
    }
    dst->ncols = src->ncols;
    dst->nrows = src->nrows;
    dstd->data = (double *)malloc(dst->ncols*dst->nrows*sizeof(double));
    for (ii1 = 0; ii1 < dst->ncols*dst->nrows; ++ii1)
        dstd->data[ii1] = 0.0;
    dst->data = (double *)malloc(dst->ncols*dst->nrows*sizeof(double));
    int i;
    for (i = 0; i < dst->ncols*dst->nrows; ++i) {
        dstd->data[i] = srcd->data[i];
        dst->data[i] = src->data[i];
    }
}

/*
  Differentiation of square_sum in forward (tangent) mode:
   variations   of useful results: square_sum
   with respect to varying inputs: *x
   Plus diff mem management of: x:in

========================================================================
                                   UTILS                                
========================================================================*/
// sum of component squares
double square_sum_d(int n, const double *x, const double *xd, double *
        square_sum) {
    int i;
    double res = x[0]*x[0];
    double resd = xd[0]*x[0] + x[0]*xd[0];
    for (i = 1; i < n; ++i) {
        resd = resd + xd[i]*x[i] + x[i]*xd[i];
        res = res + x[i]*x[i];
    }
    *square_sum = res;
    return resd;
}

/*
  Differentiation of angle_axis_to_rotation_matrix in forward (tangent) mode:
   variations   of useful results: *(*R.data)
   with respect to varying inputs: *angle_axis *(*R.data)
   Plus diff mem management of: angle_axis:in R:in *R.data:in

========================================================================
                              MAIN LOGIC                                
========================================================================*/
void angle_axis_to_rotation_matrix_d(const double *angle_axis, const double *
        angle_axisd, Matrix *R, Matrix_diff *Rd) {
    double norm;
    double normd;
    double result1;
    double result1d;
    result1d = square_sum_d(3, angle_axis, angle_axisd, &result1);
    normd = (result1 == 0.0 ? 0.0 : result1d/(2.0*sqrt(result1)));
    norm = sqrt(result1);
    if (norm < 0.0001)
        set_identity_d(R, Rd);
    else {
        double x = angle_axis[0]/norm;
        double xd = (angle_axisd[0]*norm-angle_axis[0]*normd)/(norm*norm);
        double y = angle_axis[1]/norm;
        double yd = (angle_axisd[1]*norm-angle_axis[1]*normd)/(norm*norm);
        double z = angle_axis[2]/norm;
        double zd = (angle_axisd[2]*norm-angle_axis[2]*normd)/(norm*norm);
        double s;
        double sd;
        sd = normd*cos(norm);
        s = sin(norm);
        double c;
        double cd;
        cd = -(normd*sin(norm));
        c = cos(norm);
        Rd->data[0 + 0*R->nrows] = xd*x + x*xd + (-(xd*x)-x*xd)*c + (1-x*x)*cd
        ;
        R->data[0 + 0*R->nrows] = x*x + (1-x*x)*c;
        // first row
        Rd->data[0 + 1*R->nrows] = (xd*y+x*yd)*(1-c) - x*y*cd - zd*s - z*sd;
        R->data[0 + 1*R->nrows] = x*y*(1-c) - z*s;
        Rd->data[0 + 2*R->nrows] = (xd*z+x*zd)*(1-c) - x*z*cd + yd*s + y*sd;
        R->data[0 + 2*R->nrows] = x*z*(1-c) + y*s;
        Rd->data[1 + 0*R->nrows] = (xd*y+x*yd)*(1-c) - x*y*cd + zd*s + z*sd;
        R->data[1 + 0*R->nrows] = x*y*(1-c) + z*s;
        // second row
        Rd->data[1 + 1*R->nrows] = yd*y + y*yd + (-(yd*y)-y*yd)*c + (1-y*y)*cd
        ;
        R->data[1 + 1*R->nrows] = y*y + (1-y*y)*c;
        Rd->data[1 + 2*R->nrows] = (yd*z+y*zd)*(1-c) - y*z*cd - xd*s - x*sd;
        R->data[1 + 2*R->nrows] = y*z*(1-c) - x*s;
        Rd->data[2 + 0*R->nrows] = (xd*z+x*zd)*(1-c) - x*z*cd - yd*s - y*sd;
        R->data[2 + 0*R->nrows] = x*z*(1-c) - y*s;
        // third row
        Rd->data[2 + 1*R->nrows] = (zd*y+z*yd)*(1-c) - z*y*cd + xd*s + x*sd;
        R->data[2 + 1*R->nrows] = z*y*(1-c) + x*s;
        Rd->data[2 + 2*R->nrows] = zd*z + z*zd + (-(zd*z)-z*zd)*c + (1-z*z)*cd
        ;
        R->data[2 + 2*R->nrows] = z*z + (1-z*z)*c;
    }
}

/*
  Differentiation of apply_global_transform in forward (tangent) mode:
   variations   of useful results: alloc(*(*mat.data)) *(alloc(*mat).data)
                alloc(*(*mat.data)) *(alloc(*mat).data) *(*positions.data)
   with respect to varying inputs: alloc(*(*mat.data)) *(alloc(*mat).data)
                alloc(*(*mat.data)) *(alloc(*mat).data) *(*pose_params.data)
                *(*positions.data)
   Plus diff mem management of: alloc(*mat).data:in-out alloc(*mat).data:in-out
                pose_params:in *pose_params.data:in positions:in
                *positions.data:in
*/
void apply_global_transform_d(const Matrix *pose_params, const Matrix_diff *
        pose_paramsd, Matrix *positions, Matrix_diff *positionsd) {
    int i, j;
    Matrix *R;
    Matrix_diff *Rd;
    Rd = get_new_matrix_d(3, 3, &R);
    angle_axis_to_rotation_matrix_d(pose_params->data, pose_paramsd->data, R, 
                                    Rd);
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j) {
            Rd->data[j + i*R->nrows] = Rd->data[j+i*R->nrows]*pose_params->
                data[i+1*pose_params->nrows] + R->data[j+i*R->nrows]*
                pose_paramsd->data[i+1*pose_params->nrows];
            R->data[j + i*R->nrows] *= pose_params->data[i + 1*pose_params->
            nrows];
        }
    Matrix *tmp;
    Matrix_diff *tmpd;
    tmpd = get_new_empty_matrix_d(&tmp);
    mat_mult_d(R, Rd, positions, positionsd, tmp, tmpd);
    for (j = 0; j < positions->ncols; ++j)
        for (i = 0; i < positions->nrows; ++i) {
            positionsd->data[i + j*positions->nrows] = tmpd->data[i + j*tmp->
                nrows] + pose_paramsd->data[i + 2*pose_params->nrows];
            positions->data[i + j*positions->nrows] = tmp->data[i + j*tmp->
                nrows] + pose_params->data[i + 2*pose_params->nrows];
        }
    delete_matrix_d(R, Rd);
    delete_matrix_d(tmp, tmpd);
}

/*
  Differentiation of relatives_to_absolutes in forward (tangent) mode:
   variations   of useful results: alloc(*(*dst.data)) alloc(*(*mat.data))
                *(*absolutes.data)
   with respect to varying inputs: alloc(*(*mat.data)) *(*absolutes.data)
                *(*relatives.data)
   Plus diff mem management of: absolutes:in *absolutes.data:out
                relatives:in
*/
void relatives_to_absolutes_d(int count, const Matrix *relatives, const 
        Matrix_diff *relativesd, const int *parents, Matrix *absolutes, 
        Matrix_diff *absolutesd) {
    int i;
    for (i = 0; i < count; ++i)
        if (parents[i] == -1)
            copy_d(&(absolutes[i]), &(absolutesd[i]), &(relatives[i]), &(
                   relativesd[i]));
        else
            mat_mult_d(&(absolutes[parents[i]]), &(absolutesd[parents[i]]), &(
                       relatives[i]), &(relativesd[i]), &(absolutes[i]), &(
                       absolutesd[i]));
}

/*
  Differentiation of euler_angles_to_rotation_matrix in forward (tangent) mode:
   variations   of useful results: alloc(*(*mat.data)) *(alloc(*mat).data)
                alloc(*(*mat.data)) *(alloc(*mat).data) *(*R.data)
   with respect to varying inputs: alloc(*(*mat.data)) *(alloc(*mat).data)
                alloc(*(*mat.data)) *(alloc(*mat).data) *xzy *(*R.data)
   Plus diff mem management of: alloc(*mat).data:in-out alloc(*mat).data:in-out
                xzy:in R:in *R.data:in-out
*/
void euler_angles_to_rotation_matrix_d(const double *xzy, const double *xzyd, 
        Matrix *R, Matrix_diff *Rd) {
    double tx = xzy[0];
    double txd = xzyd[0];
    double ty = xzy[2];
    double tyd = xzyd[2];
    double tz = xzy[1];
    double tzd = xzyd[1];
    Matrix *Rx;
    Matrix_diff *Rxd;
    Rxd = get_new_matrix_d(3, 3, &Rx);
    Matrix *Ry;
    Matrix_diff *Ryd;
    Ryd = get_new_matrix_d(3, 3, &Ry);
    Matrix *Rz;
    Matrix_diff *Rzd;
    Rzd = get_new_matrix_d(3, 3, &Rz);
    set_identity_d(Rx, Rxd);
    Rxd->data[1 + 1*Rx->nrows] = -(txd*sin(tx));
    Rx->data[1 + 1*Rx->nrows] = cos(tx);
    Rxd->data[2 + 1*Rx->nrows] = txd*cos(tx);
    Rx->data[2 + 1*Rx->nrows] = sin(tx);
    Rxd->data[1 + 2*Rx->nrows] = -Rxd->data[2+1*Rx->nrows];
    Rx->data[1 + 2*Rx->nrows] = -Rx->data[2+1*Rx->nrows];
    Rxd->data[2 + 2*Rx->nrows] = Rxd->data[1 + 1*Rx->nrows];
    Rx->data[2 + 2*Rx->nrows] = Rx->data[1 + 1*Rx->nrows];
    set_identity_d(Ry, Ryd);
    Ryd->data[0 + 0*Ry->nrows] = -(tyd*sin(ty));
    Ry->data[0 + 0*Ry->nrows] = cos(ty);
    Ryd->data[0 + 2*Ry->nrows] = tyd*cos(ty);
    Ry->data[0 + 2*Ry->nrows] = sin(ty);
    Ryd->data[2 + 0*Ry->nrows] = -Ryd->data[0+2*Ry->nrows];
    Ry->data[2 + 0*Ry->nrows] = -Ry->data[0+2*Ry->nrows];
    Ryd->data[2 + 2*Ry->nrows] = Ryd->data[0 + 0*Ry->nrows];
    Ry->data[2 + 2*Ry->nrows] = Ry->data[0 + 0*Ry->nrows];
    set_identity_d(Rz, Rzd);
    Rzd->data[0 + 0*Rz->nrows] = -(tzd*sin(tz));
    Rz->data[0 + 0*Rz->nrows] = cos(tz);
    Rzd->data[1 + 0*Rz->nrows] = tzd*cos(tz);
    Rz->data[1 + 0*Rz->nrows] = sin(tz);
    Rzd->data[0 + 1*Rz->nrows] = -Rzd->data[1+0*Rz->nrows];
    Rz->data[0 + 1*Rz->nrows] = -Rz->data[1+0*Rz->nrows];
    Rzd->data[1 + 1*Rz->nrows] = Rzd->data[0 + 0*Rz->nrows];
    Rz->data[1 + 1*Rz->nrows] = Rz->data[0 + 0*Rz->nrows];
    Matrix *tmp;
    Matrix_diff *tmpd;
    tmpd = get_new_empty_matrix_d(&tmp);
    mat_mult_d(Rz, Rzd, Ry, Ryd, tmp, tmpd);
    mat_mult_d(tmp, tmpd, Rx, Rxd, R, Rd);
    delete_matrix_d(Rx, Rxd);
    delete_matrix_d(Ry, Ryd);
    delete_matrix_d(Rz, Rzd);
    delete_matrix_d(tmp, tmpd);
}

/*
  Differentiation of get_posed_relatives in forward (tangent) mode:
   variations   of useful results: alloc(*(*mat.data)) *(alloc(*mat).data)
                alloc(*(*mat.data)) *(alloc(*mat).data) *(*relatives.data)
   with respect to varying inputs: alloc(*(*mat.data)) *(alloc(*mat).data)
                *(*pose_params.data)
   Plus diff mem management of: alloc(*mat).data:in-out alloc(*mat).data:in-out
                pose_params:in *pose_params.data:in base_relatives:in
                relatives:in
*/
void get_posed_relatives_d(int bone_count, const Matrix *base_relatives, const
        Matrix_diff *base_relativesd, const Matrix *pose_params, const 
        Matrix_diff *pose_paramsd, Matrix *relatives, Matrix_diff *relativesd)
{
    int i, j; /* TFIX */
    int offset = 3;
    Matrix *tr;
    Matrix_diff *trd;
    trd = get_new_matrix_d(4, 4, &tr);
    Matrix *R;
    Matrix_diff *Rd;
    Rd = get_new_matrix_d(3, 3, &R);
    /* TFIX */
    for (i = 0; i < bone_count; ++i) {
        set_identity_d(tr, trd);
        euler_angles_to_rotation_matrix_d(pose_params->data + (i+offset)*
                                          pose_params->nrows, pose_paramsd->
                                          data + (i+offset)*pose_params->nrows
                                          , R, Rd);
        set_block_d(tr, trd, 0, 0, R, Rd);
        for (j = 0; j < base_relatives->nrows * base_relatives->ncols; j++) /* TFIX */
            base_relativesd[i].data[j] = 0.0;
        mat_mult_d(&(base_relatives[i]), &(base_relativesd[i]), tr, trd, &(
                   relatives[i]), &(relativesd[i]));
    }
    delete_matrix_d(tr, trd);
    delete_matrix_d(R, Rd);
}

/*
  Differentiation of get_skinned_vertex_positions in forward (tangent) mode:
   variations   of useful results: alloc(*(*mat.data)) *(alloc(*mat).data)
                *(*positions.data)
   with respect to varying inputs: alloc(*(*mat.data)) *(alloc(*mat).data)
                *(*pose_params.data) *(*positions.data)
   Plus diff mem management of: alloc(*mat).data:in-out alloc(*mat).data:in-out
                pose_params:in *pose_params.data:in base_positions:in
                *base_positions.data:in positions:in *positions.data:in-out
                inverse_base_absolutes:in
*/
void get_skinned_vertex_positions_d(int bone_count, const Matrix *
        base_relatives, const int *parents, const Matrix *
        inverse_base_absolutes, const Matrix_diff *inverse_base_absolutesd, 
        const Matrix *base_positions, const Matrix_diff *base_positionsd, 
        const Matrix *weights, int is_mirrored, const Matrix *pose_params, 
        const Matrix_diff *pose_paramsd, Matrix *positions, Matrix_diff *
        positionsd, int apply_global) {
    int i, j; /* TFIX */
    Matrix *relatives;
    Matrix_diff *relativesd;
    Matrix_diff* base_relativesd = get_new_zero_matrix_diff_array(bone_count, base_relatives); /* TFIX */
    relativesd = get_matrix_array_d(bone_count, &relatives);
    Matrix *absolutes;
    Matrix_diff *absolutesd;
    absolutesd = get_matrix_array_d(bone_count, &absolutes);
    Matrix *transforms;
    Matrix_diff *transformsd;
    transformsd = get_matrix_array_d(bone_count, &transforms);
    get_posed_relatives_d(bone_count, base_relatives, base_relativesd, 
                          pose_params, pose_paramsd, relatives, relativesd);
    relatives_to_absolutes_d(bone_count, relatives, relativesd, parents, 
                             absolutes, absolutesd);
    // Get bone transforms->
    for (i = 0; i < bone_count; ++i) {
        for (j = 0; j < inverse_base_absolutes[i].nrows * inverse_base_absolutes[i].ncols; j++) /* TFIX */
            inverse_base_absolutesd[i].data[j] = 0.0;
        mat_mult_d(&(absolutes[i]), &(absolutesd[i]), &(inverse_base_absolutes
                   [i]), &(inverse_base_absolutesd[i]), &(transforms[i]), &(
                   transformsd[i]));
    }
    // Transform vertices by necessary transforms-> + apply skinning
    resize_d(positions, positionsd, 3, base_positions->ncols);
    fill_d(positions, positionsd, 0.0);
    Matrix *curr_positions;
    Matrix_diff *curr_positionsd;
    curr_positionsd = get_new_matrix_d(4, base_positions->ncols, &
                                       curr_positions);
    int i_bone, i_vert;
    for (i_bone = 0; i_bone < bone_count; ++i_bone) {
        for (i = 0; i < base_positions->nrows * base_positions->ncols; i++) /* TFIX */
            base_positionsd->data[i] = 0.0;
        mat_mult_d(&(transforms[i_bone]), &(transformsd[i_bone]), 
                   base_positions, base_positionsd, curr_positions, 
                   curr_positionsd);
        for (i_vert = 0; i_vert < positions->ncols; ++i_vert)
            for (i = 0; i < 3; ++i) {
                positionsd->data[i + i_vert*positions->nrows] = positionsd->
                    data[i + i_vert*positions->nrows] + weights->data[i_bone+
                    i_vert*weights->nrows]*curr_positionsd->data[i+i_vert*
                    curr_positions->nrows];
                positions->data[i + i_vert*positions->nrows] += curr_positions
                ->data[i+i_vert*curr_positions->nrows]*weights->data[i_bone+
                i_vert*weights->nrows];
            }
    }
    if (is_mirrored)
        for (i = 0; i < positions->ncols; ++i) {
            positionsd->data[0 + i*positions->nrows] = -positionsd->data[0+i*
                positions->nrows];
            positions->data[0 + i*positions->nrows] *= -1;
        }
    if (apply_global)
        apply_global_transform_d(pose_params, pose_paramsd, positions, 
                                 positionsd);
    delete_matrix_d(curr_positions, curr_positionsd);
    delete_light_matrix_array_d(relatives, relativesd, bone_count);
    delete_light_matrix_array_d(absolutes, absolutesd, bone_count);
    delete_light_matrix_array_d(transforms, transformsd, bone_count);
    delete_matrix_diff_array(bone_count, base_relativesd); /* TFIX */ // Added to dispose memory allocated in repaired code
}

/*
  Differentiation of to_pose_params in forward (tangent) mode:
   variations   of useful results: alloc(*(*mat.data)) *(*pose_params.data)
   with respect to varying inputs: *theta
   Plus diff mem management of: pose_params:in *pose_params.data:in-out
                theta:in
*/
//% !!!!!!! fixed order pose_params !!!!!
//% 1) global_rotation 2) scale 3) global_translation
//% 4) wrist
//% 5) thumb1, 6)thumb2, 7) thumb3, 8) thumb4
//%       similarly: index, middle, ring, pinky
//%       end) forearm
void to_pose_params_d(int count, const double *theta, const double *thetad, 
        const char **bone_names, Matrix *pose_params, Matrix_diff *
        pose_paramsd) {
    int i;
    resize_d0(pose_params, pose_paramsd, 3, count + 3);
    fill_d(pose_params, pose_paramsd, 0.0); /* TFIX */
    for (i = 0; i < pose_params->nrows; ++i) {
        pose_paramsd->data[i] = thetad[i];
        pose_params->data[i] = theta[i];
        pose_paramsd->data[i + 1*pose_params->nrows] = 0.0;
        pose_params->data[i + 1*pose_params->nrows] = 1.0;
        pose_paramsd->data[i + 2*pose_params->nrows] = thetad[i + 3];
        pose_params->data[i + 2*pose_params->nrows] = theta[i + 3];
    }
    int i_theta = 6;
    int i_pose_params = 5;
    int n_fingers = 5;
    int i_finger;
    for (i_finger = 0; i_finger < n_fingers; ++i_finger) {
        for (i = 2; i < 5; ++i) {
            pose_paramsd->data[0 + i_pose_params*pose_params->nrows] = thetad[
                i_theta];
            pose_params->data[0 + i_pose_params*pose_params->nrows] = theta[
                i_theta];
            i_theta++;
            if (i == 2) {
                pose_paramsd->data[1 + i_pose_params*pose_params->nrows] = 
                    thetad[i_theta];
                pose_params->data[1 + i_pose_params*pose_params->nrows] = 
                    theta[i_theta];
                i_theta++;
            }
            i_pose_params++;
        }
        i_pose_params++;
    }
}

/*
  Differentiation of hand_objective in forward (tangent) mode:
   variations   of useful results: *err
   with respect to varying inputs: *theta
   RW status of diff variables: *err:out *theta:in
   Plus diff mem management of: alloc(*mat).data:in-out alloc(*mat).data:in-out
                err:in base_positions:in *base_positions.data:in
                theta:in
*/
void hand_objective_d(const double *theta, const double *thetad, int 
        bone_count, const char **bone_names, const int *parents, Matrix *
        base_relatives, Matrix *inverse_base_absolutes, Matrix *base_positions
        , Matrix *weights, const Triangle * /* TFIX */
        triangles, int is_mirrored, int corresp_count, const int *
        correspondences, Matrix *points, double *err, double *errd) {
    Matrix_diff* base_positionsd = get_new_zero_matrix_diff(base_positions); /* TFIX */ //  Added instead of function parameter
    Matrix *pose_params;
    Matrix_diff *pose_paramsd;
    Matrix_diff* inverse_base_absolutesd = get_new_zero_matrix_diff_array(bone_count, inverse_base_absolutes); /* TFIX */
    pose_paramsd = get_new_empty_matrix_d(&pose_params);
    to_pose_params_d(bone_count, theta, thetad, bone_names, pose_params, 
                     pose_paramsd);
    Matrix *vertex_positions;
    Matrix_diff *vertex_positionsd;
    vertex_positionsd = get_new_empty_matrix_d(&vertex_positions);
    get_skinned_vertex_positions_d(bone_count, base_relatives, parents, 
                                   inverse_base_absolutes, 
                                   inverse_base_absolutesd, base_positions, 
                                   base_positionsd, weights, is_mirrored, 
                                   pose_params, pose_paramsd, vertex_positions
                                   , vertex_positionsd, 1);
    int i, j;
    *errd = 0.0;
    for (i = 0; i < corresp_count; ++i)
        for (j = 0; j < 3; ++j) {
            errd[i*3 + j] = -vertex_positionsd->data[j+correspondences[i]*
                vertex_positions->nrows];
            err[i*3 + j] = points->data[j + i*points->nrows] - 
                vertex_positions->data[j + correspondences[i]*vertex_positions
                ->nrows];
        }
    delete_matrix_d0(pose_params, pose_paramsd);
    delete_matrix_d0(vertex_positions, vertex_positionsd);
    delete_matrix_diff(base_positionsd); /* TFIX */ // Added to dispose memory allocated in repaired code
    delete_matrix_diff_array(bone_count, inverse_base_absolutesd);
}

/*
  Differentiation of hand_objective_complicated in forward (tangent) mode:
   variations   of useful results: *err
   with respect to varying inputs: *us *theta
   RW status of diff variables: *err:out *us:in *theta:in
   Plus diff mem management of: alloc(*mat).data:in-out alloc(*mat).data:in-out
                err:in us:in base_positions:in *base_positions.data:in
                theta:in
*/
void hand_objective_complicated_d(const double *theta, const double *thetad, 
        const double *us, const double *usd, int bone_count, const char **
        bone_names, const int *parents, Matrix *base_relatives, Matrix *
        inverse_base_absolutes, Matrix *base_positions, /* TFIX */
        Matrix *weights, const Triangle *triangles, int 
        is_mirrored, int corresp_count, const int *correspondences, Matrix *
        points, double *err, double *errd) {
    Matrix_diff* base_positionsd = get_new_zero_matrix_diff(base_positions); /* TFIX */ // Added instead of function parameter
    Matrix *pose_params;
    Matrix_diff *pose_paramsd;
    Matrix_diff* inverse_base_absolutesd = get_new_zero_matrix_diff_array(bone_count, inverse_base_absolutes); /* TFIX */
    pose_paramsd = get_new_empty_matrix_d(&pose_params);
    to_pose_params_d(bone_count, theta, thetad, bone_names, pose_params, 
                     pose_paramsd);
    Matrix *vertex_positions;
    Matrix_diff *vertex_positionsd;
    vertex_positionsd = get_new_empty_matrix_d(&vertex_positions);
    get_skinned_vertex_positions_d(bone_count, base_relatives, parents, 
                                   inverse_base_absolutes, 
                                   inverse_base_absolutesd, base_positions, 
                                   base_positionsd, weights, is_mirrored, 
                                   pose_params, pose_paramsd, vertex_positions
                                   , vertex_positionsd, 1);
    int i, j;
    *errd = 0.0;
    for (i = 0; i < corresp_count; ++i) {
        const int *verts = triangles[correspondences[i]].verts;
        double *u = &(us[2*i]);
        double *ud = &(usd[2*i]);
        for (j = 0; j < 3; ++j) {
            double hand_point_coord = u[0]*vertex_positions->data[j+verts[0]*
            vertex_positions->nrows] + u[1]*vertex_positions->data[j+verts[1]*
            vertex_positions->nrows] + (1.0-u[0]-u[1])*vertex_positions->data[
            j+verts[2]*vertex_positions->nrows];
            double hand_point_coordd = ud[0]*vertex_positions->data[j+verts[0]
            *vertex_positions->nrows] + u[0]*vertex_positionsd->data[j+verts[0
            ]*vertex_positions->nrows] + ud[1]*vertex_positions->data[j+verts[
            1]*vertex_positions->nrows] + u[1]*vertex_positionsd->data[j+verts
            [1]*vertex_positions->nrows] + (-ud[0]-ud[1])*vertex_positions->
            data[j+verts[2]*vertex_positions->nrows] + (1.0-u[0]-u[1])*
            vertex_positionsd->data[j+verts[2]*vertex_positions->nrows];
            errd[i*3 + j] = -hand_point_coordd;
            err[i*3 + j] = points->data[j + i*points->nrows] - 
                hand_point_coord;
        }
    }

    delete_matrix_diff(base_positionsd); /* TFIX */ // Added to dispose memory allocated in repaired code
    delete_matrix_diff_array(bone_count, inverse_base_absolutesd);
}