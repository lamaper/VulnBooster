static int dissect_h245_SET_OF_VCCapability ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_set_of ( tvb , offset , actx , tree , hf_index , ett_h245_SET_OF_VCCapability , SET_OF_VCCapability_set_of ) ;
 return offset ;
 }