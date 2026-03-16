static int dissect_h245_T_al3_sendBufferSize ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_constrained_integer ( tvb , offset , actx , tree , hf_index , 0U , 16777215U , & value , FALSE ) ;
 if ( h223_lc_params_temp && h223_lc_params_temp -> al_params ) ( ( h223_al3_params * ) h223_lc_params_temp -> al_params ) -> send_buffer_size = value & 0xfffff ;
 return offset ;
 }