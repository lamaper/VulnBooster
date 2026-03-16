static int alloc_mi ( VP9_COMMON * cm , int mi_size ) {
 int i ;
 for ( i = 0 ;
 i < 2 ;
 ++ i ) {
 cm -> mip_array [ i ] = ( MODE_INFO * ) vpx_calloc ( mi_size , sizeof ( MODE_INFO ) ) ;
 if ( cm -> mip_array [ i ] == NULL ) return 1 ;
 }
 cm -> mi_alloc_size = mi_size ;
 cm -> mi_idx = 0 ;
 cm -> prev_mi_idx = 1 ;
 cm -> mip = cm -> mip_array [ cm -> mi_idx ] ;
 cm -> prev_mip = cm -> mip_array [ cm -> prev_mi_idx ] ;
 return 0 ;
 }