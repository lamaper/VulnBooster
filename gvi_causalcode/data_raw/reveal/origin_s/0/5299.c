static void dissect_zcl_ota_imagenotify ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 guint8 payload_type ;
 payload_type = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_payload_type , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_query_jitter , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 if ( payload_type >= ZBEE_ZCL_OTA_PAYLOAD_TYPE_QJ_MC ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_manufacturer_code , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }
 if ( payload_type >= ZBEE_ZCL_OTA_PAYLOAD_TYPE_QJ_MC_IT ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_ota_image_type , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }
 if ( payload_type >= ZBEE_ZCL_OTA_PAYLOAD_TYPE_QJ_MC_IT_FV ) {
 dissect_zcl_ota_file_version_field ( tvb , tree , offset ) ;
 }
 }