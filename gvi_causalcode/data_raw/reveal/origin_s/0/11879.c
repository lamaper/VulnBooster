static int vble_unpack ( VBLEContext * ctx , GetBitContext * gb ) {
 int i ;
 for ( i = 0 ;
 i < ctx -> size ;
 i ++ ) {
 ctx -> val [ i ] = vble_read_reverse_unary ( gb ) ;
 if ( ctx -> val [ i ] == UINT8_MAX ) return - 1 ;
 }
 for ( i = 0 ;
 i < ctx -> size ;
 i ++ ) {
 if ( get_bits_left ( gb ) < ctx -> val [ i ] ) return - 1 ;
 if ( ctx -> val [ i ] ) ctx -> val [ i ] = ( 1 << ctx -> val [ i ] ) + get_bits ( gb , ctx -> val [ i ] ) - 1 ;
 }
 return 0 ;
 }