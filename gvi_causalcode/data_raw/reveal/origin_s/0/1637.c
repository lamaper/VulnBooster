static int32_t u_printf_simple_percent_handler ( const u_printf_stream_handler * handler , void * context , ULocaleBundle * formatBundle , const u_printf_spec_info * info , const ufmt_args * args ) {
 ( void ) formatBundle ;
 ( void ) info ;
 ( void ) args ;
 static const UChar PERCENT [ ] = {
 UP_PERCENT }
 ;
 return handler -> write ( context , PERCENT , 1 ) ;
 }