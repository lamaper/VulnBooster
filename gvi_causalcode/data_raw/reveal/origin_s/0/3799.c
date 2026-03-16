static void dissect_zcl_ota_imageblockrsp ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 guint8 status ;
 guint8 data_size ;
 status = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_status , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 if ( status == ZBEE_ZCL_STAT_SUCCESS ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_manufacturer_code , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_image_type , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 dissect_zcl_ota_file_version_field ( tvb , tree , offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_file_offset , tvb , * offset , 4 , ENC_LITTLE_ENDIAN ) ;
 * offset += 4 ;
 data_size = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_data_size , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_image_data , tvb , * offset , data_size , ENC_NA ) ;
 * offset += data_size ;
 }
 else if ( status == ZBEE_ZCL_STAT_OTA_WAIT_FOR_DATA ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_current_time , tvb , * offset , 4 , ENC_LITTLE_ENDIAN ) ;
 * offset += 4 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_request_time , tvb , * offset , 4 , ENC_LITTLE_ENDIAN ) ;
 * offset += 4 ;
 }
 else {
 }
 }