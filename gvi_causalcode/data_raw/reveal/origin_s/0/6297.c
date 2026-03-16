static int dissect_t38_T_seq_number ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_constrained_integer ( tvb , offset , actx , tree , hf_index , 0U , 65535U , & seq_number , FALSE ) ;

 col_append_fstr ( actx -> pinfo -> cinfo , COL_INFO , "Seq=%05u " , seq_number ) ;
 return offset ;
 }