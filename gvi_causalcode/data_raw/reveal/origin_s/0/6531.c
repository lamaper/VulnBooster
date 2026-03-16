static int dissect_h245_NumericString_SIZE_1_16 ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_NumericString ( tvb , offset , actx , tree , hf_index , 1 , 16 , FALSE ) ;
 return offset ;
 }