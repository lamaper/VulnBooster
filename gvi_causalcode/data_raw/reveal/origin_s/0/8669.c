static int dissect_h245_T_signalType ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_restricted_character_string ( tvb , offset , actx , tree , hf_index , 1 , 1 , FALSE , "0123456789#*ABCD!" , 17 , NULL ) ;
 return offset ;
 }