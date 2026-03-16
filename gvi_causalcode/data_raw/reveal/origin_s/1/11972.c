static int32_t u_printf_pointer_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 UChar result [ UPRINTF_BUFFER_SIZE ] ;
 int32_t len = UPRINTF_BUFFER_SIZE ;
 ufmt_ptou ( result , & len , args [ 0 ] . ptrValue , TRUE ) ;
 return handler -> pad_and_justify ( context , info , result , len ) ;
 }