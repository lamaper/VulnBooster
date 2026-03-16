int dissect_ber_octet_string ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id , tvbuff_t * * out_tvb ) {
 return dissect_ber_constrained_octet_string ( implicit_tag , actx , tree , tvb , offset , NO_BOUND , NO_BOUND , hf_id , out_tvb ) ;
 }