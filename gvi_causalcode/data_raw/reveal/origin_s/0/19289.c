static int dissect_ber_external_U ( gboolean implicit_tag , tvbuff_t * tvb , int offset , asn1_ctx_t * actx _U_ , proto_tree * tree , int hf_index _U_ ) {
 offset = dissect_ber_sequence ( implicit_tag , actx , tree , tvb , offset , external_U_sequence , hf_index , ett_ber_EXTERNAL ) ;
 return offset ;
 }