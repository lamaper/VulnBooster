static int dissect_h245_T_collapsing_item ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 parent_gefx = gef_ctx_get ( actx -> private_data ) ;
 actx -> private_data = gef_ctx_alloc ( parent_gefx , "collapsing" ) ;
 offset = dissect_h245_GenericParameter ( tvb , offset , actx , tree , hf_index ) ;

 return offset ;
 }