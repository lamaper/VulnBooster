static void dissect_zcl_appl_ctrl_attr_func ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 guint8 func_data_type ;
 guint16 func_id ;
 func_id = tvb_get_letohs ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_ctrl_attr_func_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 proto_item_append_text ( tree , ", %s" , val_to_str_ext_const ( func_id , & zbee_zcl_appl_ctrl_attr_names_ext , "Reserved" ) ) ;
 func_data_type = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_ctrl_attr_func_data_type , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 dissect_zcl_appl_ctrl_attr_data ( tree , tvb , offset , func_id , func_data_type ) ;
 }