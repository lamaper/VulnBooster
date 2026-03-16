static VALUE decode_enum ( unsigned char * der , long length ) {
 ASN1_ENUMERATED * ai ;
 const unsigned char * p ;
 VALUE ret ;
 int status = 0 ;
 p = der ;
 if ( ! ( ai = d2i_ASN1_ENUMERATED ( NULL , & p , length ) ) ) ossl_raise ( eASN1Error , NULL ) ;
 ret = rb_protect ( ( VALUE ( * ) ( VALUE ) ) asn1integer_to_num , ( VALUE ) ai , & status ) ;
 ASN1_ENUMERATED_free ( ai ) ;
 if ( status ) rb_jump_tag ( status ) ;
 return ret ;
 }