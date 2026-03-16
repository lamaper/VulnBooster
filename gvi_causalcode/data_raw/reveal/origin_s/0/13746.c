int dissect_ber_constrained_set_of ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * parent_tree , tvbuff_t * tvb , int offset , gint32 min_len , gint32 max_len , const ber_sequence_t * seq , gint hf_id , gint ett_id ) {
 return dissect_ber_sq_of ( implicit_tag , BER_UNI_TAG_SET , actx , parent_tree , tvb , offset , min_len , max_len , seq , hf_id , ett_id ) ;
 }