static int dissect_ber_ObjectDescriptor ( gboolean implicit_tag _U_ , tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_ber_restricted_string ( implicit_tag , BER_UNI_TAG_ObjectDescriptor , actx , tree , tvb , offset , hf_index , & actx -> external . data_value_descriptor ) ;
 return offset ;
 }