static int dissect_h225_INTEGER_1_4294967295 ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_constrained_integer ( tvb , offset , actx , tree , hf_index , 1U , 4294967295U , NULL , FALSE ) ;
 return offset ;
 }