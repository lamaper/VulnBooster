static int dissect_h245_T_elementList ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 memset ( & dummy_me , 0 , sizeof ( h223_mux_element ) ) ;
 h223_me = & dummy_me ;
 offset = dissect_per_constrained_sequence_of ( tvb , offset , actx , tree , hf_index , ett_h245_T_elementList , T_elementList_sequence_of , 1 , 256 , FALSE ) ;
 h223_me = dummy_me . next ;
 return offset ;
 }