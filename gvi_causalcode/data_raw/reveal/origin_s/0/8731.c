static int dissect_h225_H245Control_item ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_octet_string ( tvb , offset , actx , tree , hf_index , NO_BOUND , NO_BOUND , FALSE , & h245_tvb ) ;
 next_tvb_add_handle ( & h245_list , h245_tvb , ( h225_h245_in_tree ) ? tree : NULL , h245dg_handle ) ;
 return offset ;
 }