static VALUE ossl_asn1_decode_all ( VALUE self , VALUE obj ) {
 VALUE ary , val ;
 unsigned char * p ;
 long len , tmp_len = 0 , read = 0 , offset = 0 ;
 VALUE tmp ;
 obj = ossl_to_der_if_possible ( obj ) ;
 tmp = rb_str_new4 ( StringValue ( obj ) ) ;
 p = ( unsigned char * ) RSTRING_PTR ( tmp ) ;
 len = RSTRING_LEN ( tmp ) ;
 tmp_len = len ;
 ary = rb_ary_new ( ) ;
 while ( tmp_len > 0 ) {
 long tmp_read = 0 ;
 val = ossl_asn1_decode0 ( & p , tmp_len , & offset , 0 , 0 , & tmp_read ) ;
 rb_ary_push ( ary , val ) ;
 read += tmp_read ;
 tmp_len -= tmp_read ;
 }
 RB_GC_GUARD ( tmp ) ;
 int_ossl_decode_sanity_check ( len , read , offset ) ;
 return ary ;
 }