static guint8 dissect_zcl_ota_field_ctrl_field ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 guint8 field ;
 static const int * field_ctrl [ ] = {
 & hf_zbee_zcl_ota_field_ctrl_hw_ver_present , & hf_zbee_zcl_ota_field_ctrl_reserved , NULL }
 ;
 field = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_ota_field_ctrl , ett_zbee_zcl_ota_field_ctrl , field_ctrl , ENC_BIG_ENDIAN ) ;
 * offset += 1 ;
 return field ;
 }