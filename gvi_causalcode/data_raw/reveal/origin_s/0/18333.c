static void clear_mi_border ( const VP9_COMMON * cm , MODE_INFO * mi ) {
 int i ;
 vpx_memset ( mi , 0 , sizeof ( * mi ) * cm -> mi_stride ) ;
 for ( i = 1 ;
 i < cm -> mi_rows + 1 ;
 ++ i ) vpx_memset ( & mi [ i * cm -> mi_stride ] , 0 , sizeof ( * mi ) ) ;
 }