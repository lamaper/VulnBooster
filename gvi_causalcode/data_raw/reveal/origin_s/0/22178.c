static int dissect_t38_Data_Field_item ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_t38_Data_Field_item , Data_Field_item_sequence ) ;

 return offset ;
 }