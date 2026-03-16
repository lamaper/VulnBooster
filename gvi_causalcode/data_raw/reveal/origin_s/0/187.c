static int dissect_h245_H223AL2MParameters ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h245_H223AL2MParameters , H223AL2MParameters_sequence ) ;
 return offset ;
 }