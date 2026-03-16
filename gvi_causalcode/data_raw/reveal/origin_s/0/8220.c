static void dissect_zcl_ota_queryspecfilereq ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_req_node_addr , tvb , * offset , 8 , ENC_LITTLE_ENDIAN ) ;
 * offset += 8 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_manufacturer_code , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_image_type , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 dissect_zcl_ota_file_version_field ( tvb , tree , offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_zb_stack_ver , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }