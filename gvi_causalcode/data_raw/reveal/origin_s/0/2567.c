int dissect_h225_ScreeningIndicator ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_enumerated ( tvb , offset , actx , tree , hf_index , 4 , NULL , TRUE , 0 , NULL ) ;
 return offset ;
 }