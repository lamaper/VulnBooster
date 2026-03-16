static int dissect_h245_T_h223_al_type_al3 ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 h223_lc_params_temp -> al_type = al3 ;
 h223_lc_params_temp -> al_params = wmem_new ( wmem_file_scope ( ) , h223_al3_params ) ;
 }
 offset = dissect_h245_Al3 ( tvb , offset , actx , tree , hf_index ) ;
 return offset ;
 }