static void dissect_zcl_ota_attr_data ( proto_tree * tree , tvbuff_t * tvb , guint * offset , guint16 attr_id , guint data_type ) {
 switch ( attr_id ) {
 case ZBEE_ZCL_ATTR_ID_OTA_CURRENT_FILE_VERSION : case ZBEE_ZCL_ATTR_ID_OTA_DOWNLOADED_FILE_VERSION : dissect_zcl_ota_file_version_field ( tvb , tree , offset ) ;
 break ;
 case ZBEE_ZCL_ATTR_ID_OTA_CURRENT_ZB_STACK_VERSION : case ZBEE_ZCL_ATTR_ID_OTA_DOWNLOADED_ZB_STACK_VERSION : proto_tree_add_item ( tree , hf_zbee_zcl_ota_zb_stack_ver , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_OTA_IMAGE_UPGRADE_STATUS : proto_tree_add_item ( tree , hf_zbee_zcl_ota_image_upgrade_status , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_OTA_MANUFACTURER_ID : proto_tree_add_item ( tree , hf_zbee_zcl_ota_manufacturer_code , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_OTA_IMAGE_TYPE_ID : proto_tree_add_item ( tree , hf_zbee_zcl_ota_image_type , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_OTA_MIN_BLOCK_REQ_DELAY : default : dissect_zcl_attr_data ( tvb , tree , offset , data_type ) ;
 break ;
 }
 }