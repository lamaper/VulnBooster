static VALUE ossl_x509name_init_i ( RB_BLOCK_CALL_FUNC_ARGLIST ( i , args ) ) {
 VALUE self = rb_ary_entry ( args , 0 ) ;
 VALUE template = rb_ary_entry ( args , 1 ) ;
 VALUE entry [ 3 ] ;
 Check_Type ( i , T_ARRAY ) ;
 entry [ 0 ] = rb_ary_entry ( i , 0 ) ;
 entry [ 1 ] = rb_ary_entry ( i , 1 ) ;
 entry [ 2 ] = rb_ary_entry ( i , 2 ) ;
 if ( NIL_P ( entry [ 2 ] ) ) entry [ 2 ] = rb_aref ( template , entry [ 0 ] ) ;
 if ( NIL_P ( entry [ 2 ] ) ) entry [ 2 ] = DEFAULT_OBJECT_TYPE ;
 ossl_x509name_add_entry ( 3 , entry , self ) ;
 return Qnil ;
 }