int dissect_ber_relative_oid_str ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id , const char * * value_stringx ) {
 return dissect_ber_any_oid_str ( implicit_tag , actx , tree , tvb , offset , hf_id , value_stringx , FALSE ) ;
 }