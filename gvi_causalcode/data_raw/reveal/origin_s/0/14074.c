static int dissect_h245_SET_SIZE_1_65535_OF_DialingInformationNumber ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_constrained_set_of ( tvb , offset , actx , tree , hf_index , ett_h245_SET_SIZE_1_65535_OF_DialingInformationNumber , SET_SIZE_1_65535_OF_DialingInformationNumber_set_of , 1 , 65535 , FALSE ) ;
 return offset ;
 }