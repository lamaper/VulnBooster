static void dissect_zcl_appl_evtalt_alerts_struct ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_evtalt_alert_id , tvb , * offset , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_evtalt_category , tvb , * offset , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_evtalt_status , tvb , * offset , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_evtalt_reserved , tvb , * offset , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_evtalt_proprietary , tvb , * offset , 3 , ENC_BIG_ENDIAN ) ;
 * offset += 3 ;
 }