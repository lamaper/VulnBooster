static int dissect_h245_CertSelectionCriteria ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_constrained_sequence_of ( tvb , offset , actx , tree , hf_index , ett_h245_CertSelectionCriteria , CertSelectionCriteria_sequence_of , 1 , 16 , FALSE ) ;
 return offset ;
 }