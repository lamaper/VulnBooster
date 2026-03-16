static int dissect_ber_T_encoding ( gboolean implicit_tag _U_ , tvbuff_t * tvb , int offset , asn1_ctx_t * actx , proto_tree * tree , int hf_index ) {
 offset = dissect_ber_choice ( actx , tree , tvb , offset , T_encoding_choice , hf_index , ett_ber_T_encoding , & actx -> external . encoding ) ;
 return offset ;
 }