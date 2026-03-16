static gboolean dissect_rtp_heur_common ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data , gboolean check_destport ) {
 guint8 octet1 ;
 unsigned int version ;
 unsigned int offset = 0 ;
 if ( ! global_rtp_heur ) return FALSE ;
 octet1 = tvb_get_guint8 ( tvb , offset ) ;
 version = RTP_VERSION ( octet1 ) ;
 if ( version == 0 ) {
 if ( ! ( tvb_memeql ( tvb , 4 , "ZRTP" , 4 ) ) ) {
 call_dissector_only ( zrtp_handle , tvb , pinfo , tree , NULL ) ;
 return TRUE ;
 }
 else {
 switch ( global_rtp_version0_type ) {
 case RTP0_STUN : return call_dissector_only ( stun_heur_handle , tvb , pinfo , tree , NULL ) ;
 case RTP0_CLASSICSTUN : return call_dissector_only ( classicstun_heur_handle , tvb , pinfo , tree , NULL ) ;
 case RTP0_T38 : call_dissector_only ( t38_handle , tvb , pinfo , tree , NULL ) ;
 return TRUE ;
 case RTP0_SPRT : call_dissector_only ( sprt_handle , tvb , pinfo , tree , NULL ) ;
 return TRUE ;
 case RTP0_INVALID : default : return FALSE ;
 }
 }
 }
 else if ( version != 2 ) {
 return FALSE ;
 }
 if ( check_destport && ( ( pinfo -> destport % 2 ) != 0 ) ) {
 return FALSE ;
 }
 dissect_rtp ( tvb , pinfo , tree , data ) ;
 return TRUE ;
 }