int ASN1_BIT_STRING_get_bit ( ASN1_BIT_STRING * a , int n ) {
 int w , v ;
 w = n / 8 ;
 v = 1 << ( 7 - ( n & 0x07 ) ) ;
 if ( ( a == NULL ) || ( a -> length < ( w + 1 ) ) || ( a -> data == NULL ) ) return ( 0 ) ;
 return ( ( a -> data [ w ] & v ) != 0 ) ;
 }