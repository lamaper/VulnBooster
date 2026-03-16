static int dissect_h225_T_raw ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 gef_ctx_t * gefx ;
 proto_item * ti ;
 offset = dissect_per_octet_string ( tvb , offset , actx , tree , hf_index , NO_BOUND , NO_BOUND , FALSE , & value_tvb ) ;
 gefx = gef_ctx_get ( actx -> private_data ) ;
 if ( gefx ) {
 ti = proto_tree_add_string ( tree , hf_h225_debug_dissector_try_string , tvb , offset >> 3 , 0 , gefx -> key ) ;
 PROTO_ITEM_SET_HIDDEN ( ti ) ;
 dissector_try_string ( gef_content_dissector_table , gefx -> key , value_tvb , actx -> pinfo , tree , actx ) ;
 }
 return offset ;
 }