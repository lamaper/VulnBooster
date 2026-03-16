int dissect_h245_OpenLogicalChannel ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 upcoming_olc = ( ! actx -> pinfo -> fd -> flags . visited ) ? wmem_new0 ( wmem_file_scope ( ) , olc_info_t ) : NULL ;
 h223_fw_lc_num = 0 ;
 h223_lc_params_temp = NULL ;
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h245_OpenLogicalChannel , OpenLogicalChannel_sequence ) ;
 if ( h223_fw_lc_num != 0 && h223_fw_lc_params ) {
 h223_pending_olc * pending = wmem_new ( wmem_file_scope ( ) , h223_pending_olc ) ;
 pending -> fw_channel_params = h223_fw_lc_params ;
 pending -> rev_channel_params = h223_rev_lc_params ;
 temp = h223_fw_lc_num ;
 if ( actx -> pinfo -> p2p_dir > - 1 ) g_hash_table_insert ( h223_pending_olc_reqs [ actx -> pinfo -> p2p_dir ] , GINT_TO_POINTER ( temp ) , pending ) ;
 }
 if ( upcoming_olc ) {
 if ( fast_start ) {
 h245_setup_channels ( actx -> pinfo , & upcoming_olc -> rev_lc ) ;
 }
 else {
 g_hash_table_insert ( h245_pending_olc_reqs , wmem_strdup ( wmem_file_scope ( ) , gen_olc_key ( upcoming_olc -> fwd_lc_num , & actx -> pinfo -> dst , & actx -> pinfo -> src ) ) , upcoming_olc ) ;
 }
 }
 upcoming_olc = NULL ;
 if ( h245_pi != NULL ) h245_pi -> msg_type = H245_OpenLogChn ;
 return offset ;
 }