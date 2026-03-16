static int dissect_h225_TBCD_STRING ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 gboolean has_extension ;
 get_size_constraint_from_stack ( actx , "TBCD_STRING" , & min_len , & max_len , & has_extension ) ;
 offset = dissect_per_restricted_character_string ( tvb , offset , actx , tree , hf_index , min_len , max_len , has_extension , "0123456789#*abc" , 15 , NULL ) ;
 return offset ;
 }