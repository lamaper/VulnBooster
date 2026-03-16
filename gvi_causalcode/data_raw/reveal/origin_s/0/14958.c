static inline void * alloc_code_gen_buffer ( void ) {
 int flags = MAP_PRIVATE | MAP_ANONYMOUS ;
 uintptr_t start = 0 ;
 void * buf ;

 if ( tcg_ctx . code_gen_buffer_size > 800u * 1024 * 1024 ) {
 tcg_ctx . code_gen_buffer_size = 800u * 1024 * 1024 ;
 }



 return buf == MAP_FAILED ? NULL : buf ;
 }