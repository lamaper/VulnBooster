static void mp_read_codes_table ( MotionPixelsContext * mp , GetBitContext * gb ) {
 if ( mp -> codes_count == 1 ) {
 mp -> codes [ 0 ] . delta = get_bits ( gb , 4 ) ;
 }
 else {
 int i ;
 mp -> max_codes_bits = get_bits ( gb , 4 ) ;
 for ( i = 0 ;
 i < mp -> codes_count ;
 ++ i ) mp -> codes [ i ] . delta = get_bits ( gb , 4 ) ;
 mp -> current_codes_count = 0 ;
 mp_get_code ( mp , gb , 0 , 0 ) ;
 }
 }