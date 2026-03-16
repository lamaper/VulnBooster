static int dissect_ber ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 const char * name ;
 int offset ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "BER" ) ;
 col_set_str ( pinfo -> cinfo , COL_DEF_SRC , "BER encoded file" ) ;
 if ( ! decode_as_syntax ) {
 col_set_str ( pinfo -> cinfo , COL_INFO , "Unknown BER" ) ;
 offset = dissect_unknown_ber ( pinfo , tvb , 0 , tree ) ;
 }
 else {
 offset = call_ber_syntax_callback ( decode_as_syntax , tvb , 0 , pinfo , tree ) ;
 name = get_ber_oid_syntax ( decode_as_syntax ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "Decoded as %s" , name ? name : decode_as_syntax ) ;
 }
 return offset ;
 }