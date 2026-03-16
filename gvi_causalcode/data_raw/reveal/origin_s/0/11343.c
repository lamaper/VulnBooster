static void dissect_zcl_appl_evtalt_get_alerts_rsp ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_tree * sub_tree = NULL ;
 guint i ;
 guint8 count ;
 count = tvb_get_guint8 ( tvb , * offset ) & ZBEE_ZCL_APPL_EVTALT_COUNT_NUM_MASK ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_evtalt_count_num , tvb , * offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_evtalt_count_type , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 sub_tree = proto_tree_add_subtree_format ( tree , tvb , * offset , 1 , ett_zbee_zcl_appl_evtalt_alerts_struct [ i ] , NULL , "Alerts Structure #%u" , i ) ;
 dissect_zcl_appl_evtalt_alerts_struct ( tvb , sub_tree , offset ) ;
 }
 }