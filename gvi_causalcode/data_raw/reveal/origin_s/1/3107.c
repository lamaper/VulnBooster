static int32_t u_printf_string_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 UChar * s ;
 UChar buffer [ UFMT_DEFAULT_BUFFER_SIZE ] ;
 int32_t len , written ;
 int32_t argSize ;
 const char * arg = ( const char * ) ( args [ 0 ] . ptrValue ) ;
 if ( arg ) {
 argSize = ( int32_t ) strlen ( arg ) + 1 ;
 if ( argSize >= MAX_UCHAR_BUFFER_SIZE ( buffer ) ) {
 s = ufmt_defaultCPToUnicode ( arg , argSize , ( UChar * ) uprv_malloc ( MAX_UCHAR_BUFFER_NEEDED ( argSize ) ) , MAX_UCHAR_BUFFER_NEEDED ( argSize ) ) ;
 if ( s == NULL ) {
 return 0 ;
 }
 }
 else {
 s = ufmt_defaultCPToUnicode ( arg , argSize , buffer , UPRV_LENGTHOF ( buffer ) ) ;
 }
 }
 else {
 s = ( UChar * ) gNullStr ;
 }
 len = u_strlen ( s ) ;
 if ( info -> fPrecision != - 1 && info -> fPrecision < len ) {
 len = info -> fPrecision ;
 }
 written = handler -> pad_and_justify ( context , info , s , len ) ;
 if ( gNullStr != s && buffer != s ) {
 uprv_free ( s ) ;
 }
 return written ;
 }