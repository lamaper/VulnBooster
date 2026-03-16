void proto_reg_handoff_btvdp ( void ) {
 h263_handle = find_dissector_add_dependency ( "h263" , proto_btvdp ) ;
 mp4v_es_handle = find_dissector_add_dependency ( "mp4v-es" , proto_btvdp ) ;
 rtp_handle = find_dissector_add_dependency ( "rtp" , proto_btvdp ) ;
 dissector_add_string ( "bluetooth.uuid" , "1303" , btvdp_handle ) ;
 dissector_add_string ( "bluetooth.uuid" , "1304" , btvdp_handle ) ;
 dissector_add_string ( "bluetooth.uuid" , "1305" , btvdp_handle ) ;
 dissector_add_for_decode_as ( "btl2cap.cid" , btvdp_handle ) ;
 }