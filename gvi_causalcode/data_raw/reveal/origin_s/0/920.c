static void dissect_zcl_appl_evtalt_event_notif ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_evtalt_event_hdr , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_evtalt_event_id , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 }