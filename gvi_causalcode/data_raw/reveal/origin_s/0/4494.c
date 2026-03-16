void proto_reg_handoff_rtp ( void ) {
 static gboolean rtp_prefs_initialized = FALSE ;
 static dissector_handle_t rtp_rfc2198_handle ;
 static dissector_handle_t rtp_hdr_ext_ed137_handle ;
 static dissector_handle_t rtp_hdr_ext_ed137a_handle ;
 static guint rtp_saved_rfc2198_pt ;
 if ( ! rtp_prefs_initialized ) {
 rtp_handle = find_dissector ( "rtp" ) ;
 rtp_rfc2198_handle = find_dissector ( "rtp.rfc2198" ) ;
 dissector_add_handle ( "udp.port" , rtp_handle ) ;
 dissector_add_string ( "rtp_dyn_payload_type" , "red" , rtp_rfc2198_handle ) ;
 heur_dissector_add ( "udp" , dissect_rtp_heur_udp , proto_rtp ) ;
 heur_dissector_add ( "stun" , dissect_rtp_heur_stun , proto_rtp ) ;
 rtp_hdr_ext_ed137_handle = find_dissector ( "rtp.ext.ed137" ) ;
 rtp_hdr_ext_ed137a_handle = find_dissector ( "rtp.ext.ed137a" ) ;
 dissector_add_uint ( "rtp.hdr_ext" , RTP_ED137_SIG , rtp_hdr_ext_ed137_handle ) ;
 dissector_add_uint ( "rtp.hdr_ext" , RTP_ED137A_SIG , rtp_hdr_ext_ed137a_handle ) ;
 rtcp_handle = find_dissector ( "rtcp" ) ;
 data_handle = find_dissector ( "data" ) ;
 stun_handle = find_dissector ( "stun-udp" ) ;
 classicstun_handle = find_dissector ( "classicstun" ) ;
 classicstun_heur_handle = find_dissector ( "classicstun-heur" ) ;
 stun_heur_handle = find_dissector ( "stun-heur" ) ;
 t38_handle = find_dissector ( "t38" ) ;
 zrtp_handle = find_dissector ( "zrtp" ) ;
 sprt_handle = find_dissector ( "sprt" ) ;
 v150fw_handle = find_dissector ( "v150fw" ) ;
 bta2dp_content_protection_header_scms_t = find_dissector ( "bta2dp_content_protection_header_scms_t" ) ;
 btvdp_content_protection_header_scms_t = find_dissector ( "btvdp_content_protection_header_scms_t" ) ;
 bta2dp_handle = find_dissector ( "bta2dp" ) ;
 btvdp_handle = find_dissector ( "btvdp" ) ;
 sbc_handle = find_dissector ( "sbc" ) ;
 dissector_add_string ( "rtp_dyn_payload_type" , "v150fw" , v150fw_handle ) ;
 dissector_add_handle ( "btl2cap.cid" , rtp_handle ) ;
 rtp_prefs_initialized = TRUE ;
 }
 else {
 dissector_delete_uint ( "rtp.pt" , rtp_saved_rfc2198_pt , rtp_rfc2198_handle ) ;
 }
 dissector_add_uint ( "rtp.pt" , rtp_rfc2198_pt , rtp_rfc2198_handle ) ;
 rtp_saved_rfc2198_pt = rtp_rfc2198_pt ;
 }