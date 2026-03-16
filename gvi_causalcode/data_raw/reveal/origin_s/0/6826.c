static int dissect_h245_T_nonCollapsingRaw ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 gef_ctx_t * parent_gefx ;
 gef_ctx_t * gefx ;
 parent_gefx = gef_ctx_get ( actx -> private_data ) ;
 actx -> private_data = gef_ctx_alloc ( parent_gefx , "nonCollapsingRaw" ) ;
 offset = dissect_per_octet_string ( tvb , offset , actx , tree , hf_index , NO_BOUND , NO_BOUND , FALSE , & value_tvb ) ;
 gefx = gef_ctx_get ( actx -> private_data ) ;
 if ( gefx ) {
 dissector_try_string ( gef_content_dissector_table , gefx -> key , value_tvb , actx -> pinfo , tree , actx ) ;
 }
 actx -> private_data = parent_gefx ;
 return offset ;
 }