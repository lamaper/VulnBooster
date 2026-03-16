static int dissect_h225_EnumeratedParameter ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 parent_gefx = gef_ctx_get ( actx -> private_data ) ;
 actx -> private_data = gef_ctx_alloc ( parent_gefx , NULL ) ;
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h225_EnumeratedParameter , EnumeratedParameter_sequence ) ;

 return offset ;
 }