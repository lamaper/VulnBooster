static int dissect_h245_OLC_rev_multiplexParameters ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_choice ( tvb , offset , actx , tree , hf_index , ett_h245_OLC_rev_multiplexParameters , OLC_rev_multiplexParameters_choice , NULL ) ;
 return offset ;
 }