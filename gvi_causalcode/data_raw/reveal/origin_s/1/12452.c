static int dissect_h225_T_oid ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 gef_ctx_t * gefx ;
 offset = dissect_per_object_identifier_str ( tvb , offset , actx , tree , hf_index , & oid_str ) ;
 gefx = gef_ctx_get ( actx -> private_data ) ;
 if ( gefx ) gefx -> id = oid_str ;
 return offset ;
 }