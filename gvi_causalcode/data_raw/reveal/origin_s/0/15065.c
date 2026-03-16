static VALUE ossl_asn1cons_to_der ( VALUE self ) {
 int tag , tn , tc , explicit , constructed = 1 ;
 int found_prim = 0 , seq_len ;
 long length ;
 unsigned char * p ;
 VALUE value , str , inf_length ;
 tn = NUM2INT ( ossl_asn1_get_tag ( self ) ) ;
 tc = ossl_asn1_tag_class ( self ) ;
 inf_length = ossl_asn1_get_infinite_length ( self ) ;
 if ( inf_length == Qtrue ) {
 VALUE ary , example ;
 constructed = 2 ;
 if ( rb_obj_class ( self ) == cASN1Sequence || rb_obj_class ( self ) == cASN1Set ) {
 tag = ossl_asn1_default_tag ( self ) ;
 }
 else {
 ary = ossl_asn1_get_value ( self ) ;
 if ( ! rb_obj_is_kind_of ( ary , rb_cArray ) ) ossl_raise ( eASN1Error , "Constructive value must be an Array" ) ;
 while ( ! found_prim ) {
 example = rb_ary_entry ( ary , 0 ) ;
 if ( rb_obj_is_kind_of ( example , cASN1Primitive ) ) {
 found_prim = 1 ;
 }
 else {
 if ( ! rb_obj_is_kind_of ( example , cASN1Constructive ) ) {
 ossl_raise ( eASN1Error , "invalid constructed encoding" ) ;
 return Qnil ;
 }
 ary = ossl_asn1_get_value ( example ) ;
 }
 }
 tag = ossl_asn1_default_tag ( example ) ;
 }
 }
 else {
 if ( rb_obj_class ( self ) == cASN1Constructive ) ossl_raise ( eASN1Error , "Constructive shall only be used with infinite length" ) ;
 tag = ossl_asn1_default_tag ( self ) ;
 }
 explicit = ossl_asn1_is_explicit ( self ) ;
 value = join_der ( ossl_asn1_get_value ( self ) ) ;
 seq_len = ASN1_object_size ( constructed , RSTRING_LENINT ( value ) , tag ) ;
 length = ASN1_object_size ( constructed , seq_len , tn ) ;
 str = rb_str_new ( 0 , length ) ;
 p = ( unsigned char * ) RSTRING_PTR ( str ) ;
 if ( tc == V_ASN1_UNIVERSAL ) ASN1_put_object ( & p , constructed , RSTRING_LENINT ( value ) , tn , tc ) ;
 else {
 if ( explicit ) {
 ASN1_put_object ( & p , constructed , seq_len , tn , tc ) ;
 ASN1_put_object ( & p , constructed , RSTRING_LENINT ( value ) , tag , V_ASN1_UNIVERSAL ) ;
 }
 else {
 ASN1_put_object ( & p , constructed , RSTRING_LENINT ( value ) , tn , tc ) ;
 }
 }
 memcpy ( p , RSTRING_PTR ( value ) , RSTRING_LEN ( value ) ) ;
 p += RSTRING_LEN ( value ) ;
 if ( explicit && inf_length == Qtrue ) {
 ASN1_put_eoc ( & p ) ;
 }
 ossl_str_adjust ( str , p ) ;
 return str ;
 }