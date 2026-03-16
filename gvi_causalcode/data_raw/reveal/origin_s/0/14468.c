static int dissect_h225_IA5String_SIZE_1_32 ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_IA5String ( tvb , offset , actx , tree , hf_index , 1 , 32 , FALSE ) ;
 return offset ;
 }