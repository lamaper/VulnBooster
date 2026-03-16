int dissect_ber_octet_string_wcb ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id , ber_callback func ) {
 tvbuff_t * out_tvb = NULL ;
 offset = dissect_ber_octet_string ( implicit_tag , actx , tree , tvb , offset , hf_id , ( func ) ? & out_tvb : NULL ) ;
 if ( func && out_tvb && ( tvb_reported_length ( out_tvb ) > 0 ) ) {
 if ( hf_id >= 0 ) tree = proto_item_add_subtree ( actx -> created_item , ett_ber_octet_string ) ;
 func ( FALSE , out_tvb , 0 , actx , tree , - 1 ) ;
 }
 return offset ;
 }