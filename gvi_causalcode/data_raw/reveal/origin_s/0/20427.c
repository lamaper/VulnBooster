void proto_reg_handoff_bta2dp ( void ) {
 sbc_handle = find_dissector_add_dependency ( "sbc" , proto_bta2dp ) ;
 mp2t_handle = find_dissector_add_dependency ( "mp2t" , proto_bta2dp ) ;
 mpeg_audio_handle = find_dissector_add_dependency ( "mpeg-audio" , proto_bta2dp ) ;
 atrac_handle = find_dissector_add_dependency ( "atrac" , proto_bta2dp ) ;
 rtp_handle = find_dissector_add_dependency ( "rtp" , proto_bta2dp ) ;
 dissector_add_string ( "bluetooth.uuid" , "110a" , bta2dp_handle ) ;
 dissector_add_string ( "bluetooth.uuid" , "110b" , bta2dp_handle ) ;
 dissector_add_string ( "bluetooth.uuid" , "110d" , bta2dp_handle ) ;
 dissector_add_for_decode_as ( "btl2cap.cid" , bta2dp_handle ) ;
 }