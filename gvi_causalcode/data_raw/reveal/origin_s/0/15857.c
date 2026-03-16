int dissect_ber_restricted_string ( gboolean implicit_tag , gint32 type , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id , tvbuff_t * * out_tvb ) {
 return dissect_ber_constrained_restricted_string ( implicit_tag , type , actx , tree , tvb , offset , NO_BOUND , NO_BOUND , hf_id , out_tvb ) ;
 }