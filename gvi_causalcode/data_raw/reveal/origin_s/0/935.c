void fz_new_colorspace_context ( fz_context * ctx ) {
 ctx -> colorspace = fz_malloc_struct ( ctx , fz_colorspace_context ) ;
 ctx -> colorspace -> ctx_refs = 1 ;
 set_no_icc ( ctx -> colorspace ) ;


