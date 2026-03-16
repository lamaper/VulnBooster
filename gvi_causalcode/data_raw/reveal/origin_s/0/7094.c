static void dissect_zcl_ota_queryspecfilersp ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 guint8 status ;
 status = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_status , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 if ( status == ZBEE_ZCL_STAT_SUCCESS ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_manufacturer_code , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_image_type , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 dissect_zcl_ota_file_version_field ( tvb , tree , offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_image_size , tvb , * offset , 4 , ENC_LITTLE_ENDIAN ) ;
 * offset += 4 ;
 }
 }