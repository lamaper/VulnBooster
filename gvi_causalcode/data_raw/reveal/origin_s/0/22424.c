static VALUE decode_null ( unsigned char * der , long length ) {
 ASN1_NULL * null ;
 const unsigned char * p ;
 p = der ;
 if ( ! ( null = d2i_ASN1_NULL ( NULL , & p , length ) ) ) ossl_raise ( eASN1Error , NULL ) ;
 ASN1_NULL_free ( null ) ;
 return Qnil ;
 }