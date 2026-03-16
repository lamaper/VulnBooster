int ASN1_BIT_STRING_check ( ASN1_BIT_STRING * a , unsigned char * flags , int flags_len ) {
 int i , ok ;
 if ( ! a || ! a -> data ) return 1 ;
 ok = 1 ;
 for ( i = 0 ;
 i < a -> length && ok ;
 ++ i ) {
 unsigned char mask = i < flags_len ? ~ flags [ i ] : 0xff ;
 ok = ( a -> data [ i ] & mask ) == 0 ;
 }
 return ok ;
 }