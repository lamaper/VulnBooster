static void dissect_zcl_appl_stats_log_rsp ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 guint32 log_len ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_stats_utc_time , tvb , * offset , 4 , ENC_LITTLE_ENDIAN ) ;
 * offset += 4 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_stats_log_id , tvb , * offset , 4 , ENC_LITTLE_ENDIAN ) ;
 * offset += 4 ;
 log_len = tvb_get_letohl ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_stats_log_length , tvb , * offset , 4 , ENC_LITTLE_ENDIAN ) ;
 * offset += 4 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_stats_log_payload , tvb , * offset , log_len , ENC_NA ) ;
 * offset += log_len ;
 }