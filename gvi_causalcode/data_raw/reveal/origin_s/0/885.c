static int dissect_h245_ConferenceID ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_octet_string ( tvb , offset , actx , tree , hf_index , 1 , 32 , FALSE , NULL ) ;
 return offset ;
 }