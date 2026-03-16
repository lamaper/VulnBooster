static int32_t u_printf_uchar_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 ( void ) formatBundle ;
 int32_t written = 0 ;
 UChar arg = ( UChar ) ( args [ 0 ] . int64Value ) ;
 written = handler -> pad_and_justify ( context , info , & arg , 1 ) ;
 return written ;
 }