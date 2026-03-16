static VALUE join_der ( VALUE enumerable ) {
 VALUE str = rb_str_new ( 0 , 0 ) ;
 rb_block_call ( enumerable , rb_intern ( "each" ) , 0 , 0 , join_der_i , str ) ;
 return str ;
 }