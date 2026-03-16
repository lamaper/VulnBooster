static void setup_mi ( VP9_COMMON * cm ) {
 cm -> mi = cm -> mip + cm -> mi_stride + 1 ;
 cm -> prev_mi = cm -> prev_mip + cm -> mi_stride + 1 ;
 cm -> mi_grid_visible = cm -> mi_grid_base + cm -> mi_stride + 1 ;
 cm -> prev_mi_grid_visible = cm -> prev_mi_grid_base + cm -> mi_stride + 1 ;
 vpx_memset ( cm -> mip , 0 , cm -> mi_stride * ( cm -> mi_rows + 1 ) * sizeof ( * cm -> mip ) ) ;
 vpx_memset ( cm -> mi_grid_base , 0 , cm -> mi_stride * ( cm -> mi_rows + 1 ) * sizeof ( * cm -> mi_grid_base ) ) ;
 clear_mi_border ( cm , cm -> prev_mip ) ;
 }