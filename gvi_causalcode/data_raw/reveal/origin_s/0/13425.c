CYCLIC_REFRESH * vp9_cyclic_refresh_alloc ( int mi_rows , int mi_cols ) {
 CYCLIC_REFRESH * const cr = vpx_calloc ( 1 , sizeof ( * cr ) ) ;
 if ( cr == NULL ) return NULL ;
 cr -> map = vpx_calloc ( mi_rows * mi_cols , sizeof ( * cr -> map ) ) ;
 if ( cr -> map == NULL ) {
 vpx_free ( cr ) ;
 return NULL ;
 }
 return cr ;
 }