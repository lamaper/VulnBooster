static void evtag_int_test ( void ) {
 struct evbuffer * tmp = evbuffer_new ( ) ;
 uint32_t integers [ TEST_MAX_INT ] = {
 0xaf0 , 0x1000 , 0x1 , 0xdeadbeef , 0x00 , 0xbef000 }
 ;
 uint32_t integer ;
 int i ;
 for ( i = 0 ;
 i < TEST_MAX_INT ;
 i ++ ) {
 int oldlen , newlen ;
 oldlen = EVBUFFER_LENGTH ( tmp ) ;
 encode_int ( tmp , integers [ i ] ) ;
 newlen = EVBUFFER_LENGTH ( tmp ) ;
 fprintf ( stdout , "\t\tencoded 0x%08x with %d bytes\n" , integers [ i ] , newlen - oldlen ) ;
 }
 for ( i = 0 ;
 i < TEST_MAX_INT ;
 i ++ ) {
 if ( evtag_decode_int ( & integer , tmp ) == - 1 ) {
 fprintf ( stderr , "decode %d failed" , i ) ;
 exit ( 1 ) ;
 }
 if ( integer != integers [ i ] ) {
 fprintf ( stderr , "got %x, wanted %x" , integer , integers [ i ] ) ;
 exit ( 1 ) ;
 }
 }
 if ( EVBUFFER_LENGTH ( tmp ) != 0 ) {
 fprintf ( stderr , "trailing data" ) ;
 exit ( 1 ) ;
 }
 evbuffer_free ( tmp ) ;
 fprintf ( stdout , "\t%s: OK\n" , __func__ ) ;
 }