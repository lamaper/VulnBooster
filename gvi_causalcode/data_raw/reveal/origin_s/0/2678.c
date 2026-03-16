void vp9_alloc_compressor_data ( VP9_COMP * cpi ) {
 VP9_COMMON * cm = & cpi -> common ;
 vp9_alloc_context_buffers ( cm , cm -> width , cm -> height ) ;
 vpx_free ( cpi -> tok ) ;
 {
 unsigned int tokens = get_token_alloc ( cm -> mb_rows , cm -> mb_cols ) ;
 CHECK_MEM_ERROR ( cm , cpi -> tok , vpx_calloc ( tokens , sizeof ( * cpi -> tok ) ) ) ;
 }
 vp9_setup_pc_tree ( & cpi -> common , cpi ) ;
 }