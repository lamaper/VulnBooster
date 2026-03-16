static int dissect_h245_OpenLogicalChannelAck ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 int p2p_dir ;
 h223_pending_olc * pend ;
 const gchar * olc_key ;
 olc_info_t * olc_req ;
 upcoming_olc = ( ! actx -> pinfo -> fd -> flags . visited ) ? wmem_new0 ( wmem_packet_scope ( ) , olc_info_t ) : NULL ;
 h223_fw_lc_num = 0 ;
 h223_rev_lc_num = 0 ;
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h245_OpenLogicalChannelAck , OpenLogicalChannelAck_sequence ) ;
 temp = h223_fw_lc_num ;
 p2p_dir = actx -> pinfo -> p2p_dir ;
 if ( actx -> pinfo -> p2p_dir == P2P_DIR_SENT ) actx -> pinfo -> p2p_dir = P2P_DIR_RECV ;
 else actx -> pinfo -> p2p_dir = P2P_DIR_SENT ;
 pend = ( h223_pending_olc * ) g_hash_table_lookup ( h223_pending_olc_reqs [ actx -> pinfo -> p2p_dir ] , GINT_TO_POINTER ( temp ) ) ;
 if ( pend ) {
 DISSECTOR_ASSERT ( ( h223_rev_lc_num && pend -> rev_channel_params ) || ( ! h223_rev_lc_num && ! pend -> rev_channel_params ) ) ;
 if ( h223_add_lc_handle ) {
 ( * h223_add_lc_handle ) ( actx -> pinfo , h223_fw_lc_num , pend -> fw_channel_params ) ;
 if ( h223_rev_lc_num ) ( * h223_add_lc_handle ) ( actx -> pinfo , h223_rev_lc_num , pend -> rev_channel_params ) ;
 }
 }
 else {
 }
 actx -> pinfo -> p2p_dir = p2p_dir ;
 if ( upcoming_olc ) {
 olc_key = gen_olc_key ( upcoming_olc -> fwd_lc_num , & actx -> pinfo -> src , & actx -> pinfo -> dst ) ;
 olc_req = ( olc_info_t * ) g_hash_table_lookup ( h245_pending_olc_reqs , olc_key ) ;
 if ( olc_req ) {
 update_unicast_addr ( & olc_req -> fwd_lc . media_addr , & upcoming_olc -> fwd_lc . media_addr ) ;
 update_unicast_addr ( & olc_req -> fwd_lc . media_control_addr , & upcoming_olc -> fwd_lc . media_control_addr ) ;
 update_unicast_addr ( & olc_req -> rev_lc . media_addr , & upcoming_olc -> rev_lc . media_addr ) ;
 update_unicast_addr ( & olc_req -> rev_lc . media_control_addr , & upcoming_olc -> rev_lc . media_control_addr ) ;
 h245_setup_channels ( actx -> pinfo , & olc_req -> fwd_lc ) ;
 h245_setup_channels ( actx -> pinfo , & olc_req -> rev_lc ) ;
 g_hash_table_remove ( h245_pending_olc_reqs , olc_key ) ;
 }
 else {
 h245_setup_channels ( actx -> pinfo , & upcoming_olc -> fwd_lc ) ;
 }
 }
 upcoming_olc = NULL ;
 if ( h245_pi != NULL ) h245_pi -> msg_type = H245_OpenLogChnAck ;
 return offset ;
 }