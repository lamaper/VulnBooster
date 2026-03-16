void vp9_cyclic_refresh_free ( CYCLIC_REFRESH * cr ) {
 vpx_free ( cr -> map ) ;
 vpx_free ( cr ) ;
 }