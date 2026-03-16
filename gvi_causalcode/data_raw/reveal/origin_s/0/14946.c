static VALUE decode_time ( unsigned char * der , long length ) {
 ASN1_TIME * time ;
 const unsigned char * p ;
 VALUE ret ;
 int status = 0 ;
 p = der ;
 if ( ! ( time = d2i_ASN1_TIME ( NULL , & p , length ) ) ) ossl_raise ( eASN1Error , NULL ) ;
 ret = rb_protect ( ( VALUE ( * ) ( VALUE ) ) asn1time_to_time , ( VALUE ) time , & status ) ;
 ASN1_TIME_free ( time ) ;
 if ( status ) rb_jump_tag ( status ) ;
 return ret ;
 }