int ASN1_BIT_STRING_set_bit ( ASN1_BIT_STRING * a , int n , int value ) {
 int w , v , iv ;
 unsigned char * c ;
 w = n / 8 ;
 v = 1 << ( 7 - ( n & 0x07 ) ) ;
 iv = ~ v ;
 if ( ! value ) v = 0 ;
 if ( a == NULL ) return 0 ;
 a -> flags &= ~ ( ASN1_STRING_FLAG_BITS_LEFT | 0x07 ) ;
 if ( ( a -> length < ( w + 1 ) ) || ( a -> data == NULL ) ) {
 if ( ! value ) return ( 1 ) ;
 if ( a -> data == NULL ) c = ( unsigned char * ) OPENSSL_malloc ( w + 1 ) ;
 else c = ( unsigned char * ) OPENSSL_realloc_clean ( a -> data , a -> length , w + 1 ) ;
 if ( c == NULL ) {
 ASN1err ( ASN1_F_ASN1_BIT_STRING_SET_BIT , ERR_R_MALLOC_FAILURE ) ;
 return 0 ;
 }
 if ( w + 1 - a -> length > 0 ) memset ( c + a -> length , 0 , w + 1 - a -> length ) ;
 a -> data = c ;
 a -> length = w + 1 ;
 }
 a -> data [ w ] = ( ( a -> data [ w ] ) & iv ) | v ;
 while ( ( a -> length > 0 ) && ( a -> data [ a -> length - 1 ] == 0 ) ) a -> length -- ;
 return ( 1 ) ;
 }