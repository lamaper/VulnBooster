static int dissect_h245_SEQUENCE_OF_ParameterIdentifier ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_sequence_of ( tvb , offset , actx , tree , hf_index , ett_h245_SEQUENCE_OF_ParameterIdentifier , SEQUENCE_OF_ParameterIdentifier_sequence_of ) ;
 return offset ;
 }