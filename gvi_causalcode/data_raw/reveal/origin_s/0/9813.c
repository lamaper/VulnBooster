int dissect_ber_object_identifier ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id , tvbuff_t * * value_tvb ) {
 return dissect_ber_any_oid ( implicit_tag , actx , tree , tvb , offset , hf_id , value_tvb , TRUE ) ;
 }