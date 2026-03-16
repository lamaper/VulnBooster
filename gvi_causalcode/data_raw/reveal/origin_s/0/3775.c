static VALUE ossl_asn1prim_to_der ( VALUE self ) {
 ASN1_TYPE * asn1 ;
 int tn , tc , explicit ;
 long len , reallen ;
 unsigned char * buf , * p ;
 VALUE str ;
 tn = NUM2INT ( ossl_asn1_get_tag ( self ) ) ;
 tc = ossl_asn1_tag_class ( self ) ;
 explicit = ossl_asn1_is_explicit ( self ) ;
 asn1 = ossl_asn1_get_asn1type ( self ) ;
 len = ASN1_object_size ( 1 , i2d_ASN1_TYPE ( asn1 , NULL ) , tn ) ;
 if ( ! ( buf = OPENSSL_malloc ( len ) ) ) {
 ASN1_TYPE_free ( asn1 ) ;
 ossl_raise ( eASN1Error , "cannot alloc buffer" ) ;
 }
 p = buf ;
 if ( tc == V_ASN1_UNIVERSAL ) {
 i2d_ASN1_TYPE ( asn1 , & p ) ;
 }
 else if ( explicit ) {
 ASN1_put_object ( & p , 1 , i2d_ASN1_TYPE ( asn1 , NULL ) , tn , tc ) ;
 i2d_ASN1_TYPE ( asn1 , & p ) ;
 }
 else {
 i2d_ASN1_TYPE ( asn1 , & p ) ;
 * buf = tc | tn | ( * buf & V_ASN1_CONSTRUCTED ) ;
 }
 ASN1_TYPE_free ( asn1 ) ;
 reallen = p - buf ;
 assert ( reallen <= len ) ;
 str = ossl_buf2str ( ( char * ) buf , rb_long2int ( reallen ) ) ;
 return str ;
 }