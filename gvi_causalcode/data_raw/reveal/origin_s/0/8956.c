static VALUE ossl_asn1data_to_der ( VALUE self ) {
 VALUE value , der , inf_length ;
 int tag , tag_class , is_cons = 0 ;
 long length ;
 unsigned char * p ;
 value = ossl_asn1_get_value ( self ) ;
 if ( rb_obj_is_kind_of ( value , rb_cArray ) ) {
 is_cons = 1 ;
 value = join_der ( value ) ;
 }
 StringValue ( value ) ;
 tag = ossl_asn1_tag ( self ) ;
 tag_class = ossl_asn1_tag_class ( self ) ;
 inf_length = ossl_asn1_get_infinite_length ( self ) ;
 if ( inf_length == Qtrue ) {
 is_cons = 2 ;
 }
 if ( ( length = ASN1_object_size ( is_cons , RSTRING_LENINT ( value ) , tag ) ) <= 0 ) ossl_raise ( eASN1Error , NULL ) ;
 der = rb_str_new ( 0 , length ) ;
 p = ( unsigned char * ) RSTRING_PTR ( der ) ;
 ASN1_put_object ( & p , is_cons , RSTRING_LENINT ( value ) , tag , tag_class ) ;
 memcpy ( p , RSTRING_PTR ( value ) , RSTRING_LEN ( value ) ) ;
 p += RSTRING_LEN ( value ) ;
 ossl_str_adjust ( der , p ) ;
 return der ;
 }