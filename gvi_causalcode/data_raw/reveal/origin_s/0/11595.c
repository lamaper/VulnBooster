static gboolean dissect_applemidi_heur ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 guint16 command ;
 conversation_t * p_conv ;
 rtp_dyn_payload_t * rtp_dyn_payload = NULL ;
 if ( tvb_length ( tvb ) < 4 ) return FALSE ;
 if ( ! test_applemidi ( tvb , & command , FALSE ) ) {
 return FALSE ;
 }
 rtp_dyn_payload = rtp_dyn_payload_new ( ) ;
 rtp_dyn_payload_insert ( rtp_dyn_payload , 97 , "rtp-midi" , 10000 ) ;
 rtp_add_address ( pinfo , & pinfo -> src , pinfo -> srcport , 0 , APPLEMIDI_DISSECTOR_SHORTNAME , pinfo -> fd -> num , FALSE , rtp_dyn_payload ) ;
 p_conv = find_or_create_conversation ( pinfo ) ;
 conversation_set_dissector ( p_conv , applemidi_handle ) ;
 dissect_applemidi_common ( tvb , pinfo , tree , command ) ;
 return TRUE ;
 }