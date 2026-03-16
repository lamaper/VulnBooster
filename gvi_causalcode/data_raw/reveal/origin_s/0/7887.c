static int dissect_h245_INTEGER_0_4095 ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_constrained_integer ( tvb , offset , actx , tree , hf_index , 0U , 4095U , NULL , FALSE ) ;
 return offset ;
 }