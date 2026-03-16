static VALUE decode_obj ( unsigned char * der , long length ) {
 ASN1_OBJECT * obj ;
 const unsigned char * p ;
 VALUE ret ;
 int nid ;
 BIO * bio ;
 p = der ;
 if ( ! ( obj = d2i_ASN1_OBJECT ( NULL , & p , length ) ) ) ossl_raise ( eASN1Error , NULL ) ;
 if ( ( nid = OBJ_obj2nid ( obj ) ) != NID_undef ) {
 ASN1_OBJECT_free ( obj ) ;
 ret = rb_str_new2 ( OBJ_nid2sn ( nid ) ) ;
 }
 else {
 if ( ! ( bio = BIO_new ( BIO_s_mem ( ) ) ) ) {
 ASN1_OBJECT_free ( obj ) ;
 ossl_raise ( eASN1Error , NULL ) ;
 }
 i2a_ASN1_OBJECT ( bio , obj ) ;
 ASN1_OBJECT_free ( obj ) ;
 ret = ossl_membio2str ( bio ) ;
 }
 return ret ;
 }