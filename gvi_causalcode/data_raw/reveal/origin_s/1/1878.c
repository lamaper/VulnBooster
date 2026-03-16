ASN1_BIT_STRING * c2i_ASN1_BIT_STRING ( ASN1_BIT_STRING * * a , const unsigned char * * pp , long len ) {
 ASN1_BIT_STRING * ret = NULL ;
 const unsigned char * p ;
 unsigned char * s ;
 int i ;
 if ( len < 1 ) {
 i = ASN1_R_STRING_TOO_SHORT ;
 goto err ;
 }
 if ( ( a == NULL ) || ( ( * a ) == NULL ) ) {
 if ( ( ret = M_ASN1_BIT_STRING_new ( ) ) == NULL ) return ( NULL ) ;
 }
 else ret = ( * a ) ;
 p = * pp ;
 i = * ( p ++ ) ;
 ret -> flags &= ~ ( ASN1_STRING_FLAG_BITS_LEFT | 0x07 ) ;
 ret -> flags |= ( ASN1_STRING_FLAG_BITS_LEFT | ( i & 0x07 ) ) ;
 if ( len -- > 1 ) {
 s = ( unsigned char * ) OPENSSL_malloc ( ( int ) len ) ;
 if ( s == NULL ) {
 i = ERR_R_MALLOC_FAILURE ;
 goto err ;
 }
 memcpy ( s , p , ( int ) len ) ;
 s [ len - 1 ] &= ( 0xff << i ) ;
 p += len ;
 }
 else s = NULL ;
 ret -> length = ( int ) len ;
 if ( ret -> data != NULL ) OPENSSL_free ( ret -> data ) ;
 ret -> data = s ;
 ret -> type = V_ASN1_BIT_STRING ;
 if ( a != NULL ) ( * a ) = ret ;
 * pp = p ;
 return ( ret ) ;
 err : ASN1err ( ASN1_F_C2I_ASN1_BIT_STRING , i ) ;
 if ( ( ret != NULL ) && ( ( a == NULL ) || ( * a != ret ) ) ) M_ASN1_BIT_STRING_free ( ret ) ;
 return ( NULL ) ;
 }