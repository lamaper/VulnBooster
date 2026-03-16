static int32_t u_printf_char_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 UChar s [ U16_MAX_LENGTH + 1 ] ;
 int32_t len = 1 , written ;
 unsigned char arg = ( unsigned char ) ( args [ 0 ] . int64Value ) ;
 ufmt_defaultCPToUnicode ( ( const char * ) & arg , 2 , s , UPRV_LENGTHOF ( s ) ) ;
 if ( arg != 0 ) {
 len = u_strlen ( s ) ;
 }
 written = handler -> pad_and_justify ( context , info , s , len ) ;
 return written ;
 }