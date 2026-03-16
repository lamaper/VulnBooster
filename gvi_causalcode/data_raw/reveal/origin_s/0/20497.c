static int dissect_ber_any_oid_str ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id , const char * * value_stringx , gboolean is_absolute ) {
 tvbuff_t * value_tvb = NULL ;
 guint length ;
 offset = dissect_ber_any_oid ( implicit_tag , actx , tree , tvb , offset , hf_id , ( value_stringx ) ? & value_tvb : NULL , is_absolute ) ;
 if ( value_stringx ) {
 if ( value_tvb && ( length = tvb_reported_length ( value_tvb ) ) ) {
 * value_stringx = oid_encoded2string ( wmem_packet_scope ( ) , tvb_get_ptr ( value_tvb , 0 , length ) , length ) ;
 }
 else {
 * value_stringx = "" ;
 }
 }
 return offset ;
 }