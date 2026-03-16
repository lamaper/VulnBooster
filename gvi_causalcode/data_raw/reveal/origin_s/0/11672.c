static void dissect_zcl_ota_querynextimagereq ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 guint8 field_ctrl ;
 field_ctrl = dissect_zcl_ota_field_ctrl_field ( tvb , tree , offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_manufacturer_code , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_image_type , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 dissect_zcl_ota_file_version_field ( tvb , tree , offset ) ;
 if ( field_ctrl & ZBEE_ZCL_OTA_FIELD_CTRL_HW_VER_PRESENT ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_hw_version , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }
 }