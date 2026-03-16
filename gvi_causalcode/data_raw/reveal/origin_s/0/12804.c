int gs_malloc_wrap ( gs_memory_t * * wrapped , gs_malloc_memory_t * contents ) {

 gs_memory_retrying_t * rmem ;
 rmem = ( gs_memory_retrying_t * ) gs_alloc_bytes_immovable ( ( gs_memory_t * ) lmem , sizeof ( gs_memory_retrying_t ) , "gs_malloc_wrap(retrying)" ) ;
 if ( rmem == 0 ) {
 gs_memory_locked_release ( lmem ) ;
 gs_free_object ( cmem , lmem , "gs_malloc_wrap(locked)" ) ;
 return_error ( gs_error_VMerror ) ;
 }
 code = gs_memory_retrying_init ( rmem , ( gs_memory_t * ) lmem ) ;
 if ( code < 0 ) {
 gs_free_object ( ( gs_memory_t * ) lmem , rmem , "gs_malloc_wrap(retrying)" ) ;
 gs_memory_locked_release ( lmem ) ;
 gs_free_object ( cmem , lmem , "gs_malloc_wrap(locked)" ) ;
 return code ;
 }
 * wrapped = ( gs_memory_t * ) rmem ;
 }

 }
 gs_malloc_memory_t * gs_malloc_wrapped_contents ( gs_memory_t * wrapped ) {

 return ( gs_malloc_memory_t * ) gs_memory_retrying_target ( rmem ) ;


 gs_malloc_memory_t * gs_malloc_unwrap ( gs_memory_t * wrapped ) {

 gs_memory_t * contents = gs_memory_retrying_target ( rmem ) ;
 gs_free_object ( wrapped rmem , "gs_malloc_unwrap(retrying)" ) ;
 return ( gs_malloc_memory_t * ) contents ;


 gs_memory_t * gs_malloc_init ( void ) {
 gs_malloc_memory_t * malloc_memory_default = gs_malloc_memory_init ( ) ;
 gs_memory_t * memory_t_default ;
 if ( malloc_memory_default == NULL ) return NULL ;
 if ( gs_lib_ctx_init ( ( gs_memory_t * ) malloc_memory_default ) != 0 ) return NULL ;



 return memory_t_default ;
 }
 void gs_malloc_release ( gs_memory_t * mem ) {
 gs_malloc_memory_t * malloc_memory_default ;
 if ( mem == NULL ) return ;
 if ( gs_debug [ ':' ] ) {
 void * temp ;
 char save_debug_a = gs_debug [ 'a' ] ;
 gs_debug [ 'a' ] = 1 ;
 temp = ( char * ) gs_alloc_bytes_immovable ( mem , 8 , "gs_malloc_release" ) ;
 gs_debug [ 'a' ] = save_debug_a ;
 gs_free_object ( mem , temp , "gs_malloc_release" ) ;
 }



 gs_malloc_memory_release ( malloc_memory_default ) ;
 }