static int dissect_t38_Type_of_msg ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_choice ( tvb , offset , actx , tree , hf_index , ett_t38_Type_of_msg , Type_of_msg_choice , & Type_of_msg_value ) ;

 return offset ;
 }