static VALUE decode_bstr ( unsigned char * der , long length , long * unused_bits ) {
 ASN1_BIT_STRING * bstr ;
 const unsigned char * p ;
 long len ;
 VALUE ret ;
 p = der ;
 if ( ! ( bstr = d2i_ASN1_BIT_STRING ( NULL , & p , length ) ) ) ossl_raise ( eASN1Error , NULL ) ;
 len = bstr -> length ;
 * unused_bits = 0 ;
 if ( bstr -> flags & ASN1_STRING_FLAG_BITS_LEFT ) * unused_bits = bstr -> flags & 0x07 ;
 ret = rb_str_new ( ( const char * ) bstr -> data , len ) ;
 ASN1_BIT_STRING_free ( bstr ) ;
 return ret ;
 }