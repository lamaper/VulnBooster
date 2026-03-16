static VALUE join_der_i ( RB_BLOCK_CALL_FUNC_ARGLIST ( i , str ) ) {
 i = ossl_to_der_if_possible ( i ) ;
 StringValue ( i ) ;
 rb_str_append ( str , i ) ;
 return Qnil ;
 }