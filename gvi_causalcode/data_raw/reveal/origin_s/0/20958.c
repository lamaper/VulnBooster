static int decode_block_type ( RangeCoder * c , BlockTypeContext * bt ) {
 bt -> last_type = rac_get_model_sym ( c , & bt -> bt_model [ bt -> last_type ] ) ;
 return bt -> last_type ;
 }