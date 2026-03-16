int dissect_ber_sequence_of ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * parent_tree , tvbuff_t * tvb , int offset , const ber_sequence_t * seq , gint hf_id , gint ett_id ) {
 return dissect_ber_sq_of ( implicit_tag , BER_UNI_TAG_SEQUENCE , actx , parent_tree , tvb , offset , NO_BOUND , NO_BOUND , seq , hf_id , ett_id ) ;
 }