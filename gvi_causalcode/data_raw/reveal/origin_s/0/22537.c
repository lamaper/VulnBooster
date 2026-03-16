static inline void invalidate_page_bitmap ( PageDesc * p ) {
 if ( p -> code_bitmap ) {
 g_free ( p -> code_bitmap ) ;
 p -> code_bitmap = NULL ;
 }
 p -> code_write_count = 0 ;
 }