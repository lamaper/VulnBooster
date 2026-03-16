static void dissect_ipmb_state_notify ( tvbuff_t * tvb , proto_tree * tree ) {
 proto_tree_add_item ( tree , hf_trace_notify_format , tvb , 0 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_bitmask ( tree , tvb , 1 , hf_trace_ipmb_state , ett_trace_ipmb_state , bits_chn_state_info , ENC_LITTLE_ENDIAN ) ;
 }