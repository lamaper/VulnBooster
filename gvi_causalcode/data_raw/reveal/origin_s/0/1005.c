static VALUE int_ossl_asn1_decode0_prim ( unsigned char * * pp , long length , long hlen , int tag , VALUE tc , long * num_read ) {
 VALUE value , asn1data ;
 unsigned char * p ;
 long flag = 0 ;
 p = * pp ;
 if ( tc == sym_UNIVERSAL && tag < ossl_asn1_info_size ) {
 switch ( tag ) {
 case V_ASN1_EOC : value = decode_eoc ( p , hlen + length ) ;
 break ;
 case V_ASN1_BOOLEAN : value = decode_bool ( p , hlen + length ) ;
 break ;
 case V_ASN1_INTEGER : value = decode_int ( p , hlen + length ) ;
 break ;
 case V_ASN1_BIT_STRING : value = decode_bstr ( p , hlen + length , & flag ) ;
 break ;
 case V_ASN1_NULL : value = decode_null ( p , hlen + length ) ;
 break ;
 case V_ASN1_ENUMERATED : value = decode_enum ( p , hlen + length ) ;
 break ;
 case V_ASN1_OBJECT : value = decode_obj ( p , hlen + length ) ;
 break ;
 case V_ASN1_UTCTIME : case V_ASN1_GENERALIZEDTIME : value = decode_time ( p , hlen + length ) ;
 break ;
 default : p += hlen ;
 value = rb_str_new ( ( const char * ) p , length ) ;
 break ;
 }
 }
 else {
 p += hlen ;
 value = rb_str_new ( ( const char * ) p , length ) ;
 }
 * pp += hlen + length ;
 * num_read = hlen + length ;
 if ( tc == sym_UNIVERSAL && tag < ossl_asn1_info_size && ossl_asn1_info [ tag ] . klass ) {
 VALUE klass = * ossl_asn1_info [ tag ] . klass ;
 VALUE args [ 4 ] ;
 args [ 0 ] = value ;
 args [ 1 ] = INT2NUM ( tag ) ;
 args [ 2 ] = Qnil ;
 args [ 3 ] = tc ;
 asn1data = rb_obj_alloc ( klass ) ;
 ossl_asn1_initialize ( 4 , args , asn1data ) ;
 if ( tag == V_ASN1_BIT_STRING ) {
 rb_ivar_set ( asn1data , sivUNUSED_BITS , LONG2NUM ( flag ) ) ;
 }
 }
 else {
 asn1data = rb_obj_alloc ( cASN1Data ) ;
 ossl_asn1data_initialize ( asn1data , value , INT2NUM ( tag ) , tc ) ;
 }
 return asn1data ;
 }