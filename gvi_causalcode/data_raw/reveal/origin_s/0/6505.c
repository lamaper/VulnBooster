static int dissect_s_supervisor_exception_detail ( proto_tree * tree , proto_item * item , tvbuff_t * tvb , int offset , int hf_size , int hf_data ) {
 int size ;
 proto_tree_add_item ( tree , hf_size , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 size = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_data , tvb , offset + 1 , size , ENC_NA ) ;
 proto_item_set_len ( item , size + 1 ) ;
 return size + 1 ;
 }