static void dissect_zcl_ota_file_version_field ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 static const int * file_version [ ] = {
 & hf_zbee_zcl_ota_file_version_appl_release , & hf_zbee_zcl_ota_file_version_appl_build , & hf_zbee_zcl_ota_file_version_stack_release , & hf_zbee_zcl_ota_file_version_stack_build , NULL }
 ;
 proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_ota_file_version , ett_zbee_zcl_ota_file_version , file_version , ENC_BIG_ENDIAN ) ;
 * offset += 4 ;
 }