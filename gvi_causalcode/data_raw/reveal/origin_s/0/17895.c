static int dissect_h245_MultiplexElement ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 h223_me -> next = me ;
 h223_me = me ;
 h223_me -> next = NULL ;
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h245_MultiplexElement , MultiplexElement_sequence ) ;
 return offset ;
 }