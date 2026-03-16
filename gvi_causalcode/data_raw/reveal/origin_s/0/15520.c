void vp9_swap_mi_and_prev_mi ( VP9_COMMON * cm ) {
 const int tmp = cm -> mi_idx ;
 cm -> mi_idx = cm -> prev_mi_idx ;
 cm -> prev_mi_idx = tmp ;
 cm -> mip = cm -> mip_array [ cm -> mi_idx ] ;
 cm -> prev_mip = cm -> mip_array [ cm -> prev_mi_idx ] ;
 cm -> mi = cm -> mip + cm -> mi_stride + 1 ;
 cm -> prev_mi = cm -> prev_mip + cm -> mi_stride + 1 ;
 }