static int32_t u_printf_count_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 ( void ) handler ;
 ( void ) context ;
 ( void ) formatBundle ;
 int32_t * count = ( int32_t * ) ( args [ 0 ] . ptrValue ) ;
 * count = info -> fWidth ;
 return 0 ;
 }