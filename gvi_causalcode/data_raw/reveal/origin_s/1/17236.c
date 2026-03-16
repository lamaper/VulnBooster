static int32_t u_printf_ustring_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 int32_t len , written ;
 const UChar * arg = ( const UChar * ) ( args [ 0 ] . ptrValue ) ;
 if ( arg == NULL ) {
 arg = gNullStr ;
 }
 len = u_strlen ( arg ) ;
 if ( info -> fPrecision != - 1 && info -> fPrecision < len ) {
 len = info -> fPrecision ;
 }
 written = handler -> pad_and_justify ( context , info , arg , len ) ;
 return written ;
 }