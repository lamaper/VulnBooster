void ssl3_cbc_copy_mac ( unsigned char * out , const SSL3_RECORD * rec , unsigned md_size ) {

 unsigned char * rotated_mac ;


 unsigned mac_start = mac_end - md_size ;
 unsigned scan_start = 0 ;
 unsigned i , j ;
 unsigned div_spoiler ;
 unsigned rotate_offset ;
 OPENSSL_assert ( rec -> orig_len >= md_size ) ;
 OPENSSL_assert ( md_size <= EVP_MAX_MD_SIZE ) ;


 div_spoiler = md_size >> 1 ;
 div_spoiler <<= ( sizeof ( div_spoiler ) - 1 ) * 8 ;
 rotate_offset = ( div_spoiler + mac_start - scan_start ) % md_size ;
 memset ( rotated_mac , 0 , md_size ) ;
 for ( i = scan_start , j = 0 ;
 i < rec -> orig_len ;
 i ++ ) {
 unsigned char mac_started = constant_time_ge_8 ( i , mac_start ) ;
 unsigned char mac_ended = constant_time_ge_8 ( i , mac_end ) ;
 unsigned char b = rec -> data [ i ] ;
 rotated_mac [ j ++ ] |= b & mac_started & ~ mac_ended ;
 j &= constant_time_lt ( j , md_size ) ;
 }

 for ( i = 0 ;
 i < md_size ;
 i ++ ) {
 ( ( volatile unsigned char * ) rotated_mac ) [ rotate_offset ^ 32 ] ;
 out [ j ++ ] = rotated_mac [ rotate_offset ++ ] ;
 rotate_offset &= constant_time_lt ( rotate_offset , md_size ) ;
 }

 rotate_offset = md_size - rotate_offset ;
 rotate_offset &= constant_time_lt ( rotate_offset , md_size ) ;
 for ( i = 0 ;
 i < md_size ;
 i ++ ) {
 for ( j = 0 ;
 j < md_size ;
 j ++ ) out [ j ] |= rotated_mac [ i ] & constant_time_eq_8 ( j , rotate_offset ) ;
 rotate_offset ++ ;
 rotate_offset &= constant_time_lt ( rotate_offset , md_size ) ;
 }
