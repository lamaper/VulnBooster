static int dissect_t38_T30_indicator ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_enumerated ( tvb , offset , actx , tree , hf_index , 16 , & T30ind_value , TRUE , 7 , NULL ) ;

 col_append_fstr ( actx -> pinfo -> cinfo , COL_INFO , " t30ind: %s" , val_to_str ( T30ind_value , t38_T30_indicator_vals , "<unknown>" ) ) ;
 }
 if ( primary_part ) t38_info -> t30ind_value = T30ind_value ;
 return offset ;
 }