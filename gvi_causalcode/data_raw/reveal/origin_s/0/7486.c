static void free_mi ( VP9_COMMON * cm ) {
 int i ;
 for ( i = 0 ;
 i < 2 ;
 ++ i ) {
 vpx_free ( cm -> mip_array [ i ] ) ;
 cm -> mip_array [ i ] = NULL ;
 }
 cm -> mip = NULL ;
 cm -> prev_mip = NULL ;
 }