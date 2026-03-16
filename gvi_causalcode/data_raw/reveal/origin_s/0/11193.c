static int dissect_h245_T_standard ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 gef_ctx_t * gefx ;
 offset = dissect_per_constrained_integer ( tvb , offset , actx , tree , hf_index , 0U , 127U , & value_int , FALSE ) ;
 gefx = gef_ctx_get ( actx -> private_data ) ;
 if ( gefx ) gefx -> id = wmem_strdup_printf ( wmem_packet_scope ( ) , "%d" , value_int ) ;
 return offset ;
 }