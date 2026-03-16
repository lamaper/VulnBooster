static int dissect_steam_ihs_discovery ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 proto_item * ti ;
 proto_tree * steam_ihs_discovery_tree ;
 gint offset = 0 ;
 gint header_length = 0 ;
 gint body_length = 0 ;
 gint total_length = 0 ;
 gint64 msg_type ;
 if ( tvb_reported_length ( tvb ) < STEAM_IHS_DISCOVERY_MIN_LENGTH ) return 0 ;
 if ( tvb_captured_length ( tvb ) < STEAM_IHS_DISCOVERY_MIN_LENGTH ) return 0 ;
 if ( tvb_get_ntoh64 ( tvb , 0 ) != STEAM_IHS_DISCOVERY_SIGNATURE_VALUE ) return 0 ;
 header_length = tvb_get_letohl ( tvb , STEAM_IHS_DISCOVERY_SIGNATURE_LENGTH ) ;
 body_length = tvb_get_letohl ( tvb , STEAM_IHS_DISCOVERY_SIGNATURE_LENGTH + 4 + header_length ) ;
 total_length = STEAM_IHS_DISCOVERY_SIGNATURE_LENGTH + 4 + header_length + 4 + body_length ;
 if ( tvb_reported_length ( tvb ) != ( guint ) total_length ) return 0 ;
 if ( tvb_captured_length ( tvb ) != ( guint ) total_length ) return 0 ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "STEAMDISCOVER" ) ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 ti = proto_tree_add_item ( tree , proto_steam_ihs_discovery , tvb , 0 , - 1 , ENC_NA ) ;
 steam_ihs_discovery_tree = proto_item_add_subtree ( ti , ett_steam_ihs_discovery ) ;
 proto_tree_add_item ( steam_ihs_discovery_tree , hf_steam_ihs_discovery_signature , tvb , offset , STEAM_IHS_DISCOVERY_SIGNATURE_LENGTH , ENC_LITTLE_ENDIAN ) ;
 offset += STEAM_IHS_DISCOVERY_SIGNATURE_LENGTH ;
 proto_tree_add_item ( steam_ihs_discovery_tree , hf_steam_ihs_discovery_header_length , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 msg_type = steamdiscover_dissect_header ( tvb , pinfo , steam_ihs_discovery_tree , offset , header_length ) ;
 if ( ( 0 <= msg_type ) && ( msg_type <= STEAMDISCOVER_MSGTYPES_MAX ) ) {
 col_set_str ( pinfo -> cinfo , COL_INFO , hf_steam_ihs_discovery_header_msgtype_strings [ msg_type ] . strptr ) ;
 }
 else {
 col_set_str ( pinfo -> cinfo , COL_INFO , "Unknown Message" ) ;
 }
 offset += header_length ;
 proto_tree_add_item ( steam_ihs_discovery_tree , hf_steam_ihs_discovery_body_length , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 switch ( msg_type ) {
 case STEAMDISCOVER_MSGTYPE_CLIENTBROADCASTMSGDISCOVERY : steamdiscover_dissect_body_discovery ( tvb , pinfo , steam_ihs_discovery_tree , offset , body_length ) ;
 break ;
 case STEAMDISCOVER_MSGTYPE_CLIENTBROADCASTMSGSTATUS : steamdiscover_dissect_body_status ( tvb , pinfo , steam_ihs_discovery_tree , offset , body_length ) ;
 break ;
 case STEAMDISCOVER_MSGTYPE_CLIENTBROADCASTMSGOFFLINE : break ;
 case STEAMDISCOVER_MSGTYPE_DEVICEAUTHORIZATIONREQUEST : steamdiscover_dissect_body_authrequest ( tvb , pinfo , steam_ihs_discovery_tree , offset , body_length ) ;
 break ;
 case STEAMDISCOVER_MSGTYPE_DEVICEAUTHORIZATIONCANCELREQUEST : break ;
 case STEAMDISCOVER_MSGTYPE_DEVICEAUTHORIZATIONRESPONSE : steamdiscover_dissect_body_authresponse ( tvb , pinfo , steam_ihs_discovery_tree , offset , body_length ) ;
 break ;
 case STEAMDISCOVER_MSGTYPE_DEVICESTREAMINGREQUEST : steamdiscover_dissect_body_streamingrequest ( tvb , pinfo , steam_ihs_discovery_tree , offset , body_length ) ;
 break ;
 case STEAMDISCOVER_MSGTYPE_DEVICESTREAMINGCANCELREQUEST : steamdiscover_dissect_body_streamingcancelrequest ( tvb , pinfo , steam_ihs_discovery_tree , offset , body_length ) ;
 break ;
 case STEAMDISCOVER_MSGTYPE_DEVICESTREAMINGRESPONSE : steamdiscover_dissect_body_streamingresponse ( tvb , pinfo , steam_ihs_discovery_tree , offset , body_length ) ;
 break ;
 case STEAMDISCOVER_MSGTYPE_DEVICEPROOFREQUEST : steamdiscover_dissect_body_proofrequest ( tvb , pinfo , steam_ihs_discovery_tree , offset , body_length ) ;
 break ;
 case STEAMDISCOVER_MSGTYPE_DEVICEPROOFRESPONSE : steamdiscover_dissect_body_proofresponse ( tvb , pinfo , steam_ihs_discovery_tree , offset , body_length ) ;
 break ;
 default : steamdiscover_dissect_body_unknown ( tvb , pinfo , steam_ihs_discovery_tree , offset , body_length ) ;
 break ;
 }
 return tvb_captured_length ( tvb ) ;
 }