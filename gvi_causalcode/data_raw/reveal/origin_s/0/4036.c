static gchar * rtmpt_get_packet_desc ( tvbuff_t * tvb , guint32 offset , guint32 remain , rtmpt_conv_t * rconv , int cdir , rtmpt_packet_t * tp , gint * deschasopcode ) {
 if ( tp -> cmd == RTMPT_TYPE_CHUNK_SIZE || tp -> cmd == RTMPT_TYPE_ABORT_MESSAGE || tp -> cmd == RTMPT_TYPE_ACKNOWLEDGEMENT || tp -> cmd == RTMPT_TYPE_WINDOW ) {
 if ( tp -> len >= 4 && remain >= 4 ) {
 * deschasopcode = TRUE ;
 return wmem_strdup_printf ( wmem_packet_scope ( ) , "%s %d" , val_to_str ( tp -> cmd , rtmpt_opcode_vals , "Unknown (0x%01x)" ) , tvb_get_ntohl ( tvb , offset ) ) ;
 }
 }
 else if ( tp -> cmd == RTMPT_TYPE_PEER_BANDWIDTH ) {
 if ( tp -> len >= 5 && remain >= 5 ) {
 * deschasopcode = TRUE ;
 return wmem_strdup_printf ( wmem_packet_scope ( ) , "%s %d,%s" , val_to_str ( tp -> cmd , rtmpt_opcode_vals , "Unknown (0x%01x)" ) , tvb_get_ntohl ( tvb , offset ) , val_to_str ( tvb_get_guint8 ( tvb , offset + 4 ) , rtmpt_limit_vals , "Unknown (%d)" ) ) ;
 }
 }
 else if ( tp -> cmd == RTMPT_TYPE_UCM ) {
 guint16 iUCM = - 1 ;
 const gchar * sFunc ;
 const gchar * sParam = "" ;
 if ( tp -> len < 2 || remain < 2 ) return NULL ;
 iUCM = tvb_get_ntohs ( tvb , offset ) ;
 sFunc = try_val_to_str ( iUCM , rtmpt_ucm_vals ) ;
 if ( sFunc == NULL ) {
 * deschasopcode = TRUE ;
 sFunc = wmem_strdup_printf ( wmem_packet_scope ( ) , "User Control Message 0x%01x" , iUCM ) ;
 }
 if ( iUCM == RTMPT_UCM_STREAM_BEGIN || iUCM == RTMPT_UCM_STREAM_EOF || iUCM == RTMPT_UCM_STREAM_DRY || iUCM == RTMPT_UCM_STREAM_ISRECORDED ) {
 if ( tp -> len >= 6 && remain >= 6 ) {
 sParam = wmem_strdup_printf ( wmem_packet_scope ( ) , " %d" , tvb_get_ntohl ( tvb , offset + 2 ) ) ;
 }
 }
 else if ( iUCM == RTMPT_UCM_SET_BUFFER ) {
 if ( tp -> len >= 10 && remain >= 10 ) {
 sParam = wmem_strdup_printf ( wmem_packet_scope ( ) , " %d,%dms" , tvb_get_ntohl ( tvb , offset + 2 ) , tvb_get_ntohl ( tvb , offset + 6 ) ) ;
 }
 }
 return wmem_strdup_printf ( wmem_packet_scope ( ) , "%s%s" , sFunc , sParam ) ;
 }
 else if ( tp -> cmd == RTMPT_TYPE_COMMAND_AMF0 || tp -> cmd == RTMPT_TYPE_COMMAND_AMF3 || tp -> cmd == RTMPT_TYPE_DATA_AMF0 || tp -> cmd == RTMPT_TYPE_DATA_AMF3 ) {
 guint32 slen = 0 ;
 guint32 soff = 0 ;
 gchar * sFunc = NULL ;
 gchar * sParam = NULL ;
 if ( tp -> cmd == RTMPT_TYPE_COMMAND_AMF3 || tp -> cmd == RTMPT_TYPE_DATA_AMF3 ) {
 soff = 1 ;
 }
 if ( tp -> len >= 3 + soff && remain >= 3 + soff ) {
 slen = tvb_get_ntohs ( tvb , offset + 1 + soff ) ;
 }
 if ( slen > 0 ) {
 sFunc = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset + 3 + soff , slen , ENC_ASCII ) ;
 RTMPT_DEBUG ( "got function call '%s'\n" , sFunc ) ;
 if ( strcmp ( sFunc , "connect" ) == 0 ) {
 sParam = rtmpt_get_amf_param ( tvb , offset + soff , 2 , "app" ) ;
 }
 else if ( strcmp ( sFunc , "play" ) == 0 ) {
 sParam = rtmpt_get_amf_param ( tvb , offset + soff , 3 , NULL ) ;
 }
 else if ( strcmp ( sFunc , "play2" ) == 0 ) {
 sParam = rtmpt_get_amf_param ( tvb , offset + soff , 3 , "streamName" ) ;
 }
 else if ( strcmp ( sFunc , "releaseStream" ) == 0 ) {
 sParam = rtmpt_get_amf_param ( tvb , offset + soff , 3 , NULL ) ;
 }
 else if ( strcmp ( sFunc , "FCPublish" ) == 0 ) {
 sParam = rtmpt_get_amf_param ( tvb , offset + soff , 3 , NULL ) ;
 }
 else if ( strcmp ( sFunc , "publish" ) == 0 ) {
 sParam = rtmpt_get_amf_param ( tvb , offset + soff , 3 , NULL ) ;
 }
 else if ( strcmp ( sFunc , "onStatus" ) == 0 ) {
 if ( tp -> cmd == RTMPT_TYPE_COMMAND_AMF0 || tp -> cmd == RTMPT_TYPE_COMMAND_AMF3 ) {
 sParam = rtmpt_get_amf_param ( tvb , offset + soff , 3 , "code" ) ;
 }
 else {
 sParam = rtmpt_get_amf_param ( tvb , offset + soff , 1 , "code" ) ;
 }
 }
 else if ( strcmp ( sFunc , "onPlayStatus" ) == 0 ) {
 sParam = rtmpt_get_amf_param ( tvb , offset + soff , 1 , "code" ) ;
 }
 else if ( strcmp ( sFunc , "_result" ) == 0 ) {
 sParam = rtmpt_get_amf_param ( tvb , offset + soff , 3 , "code" ) ;
 tp -> isresponse = TRUE ;
 }
 else if ( strcmp ( sFunc , "_error" ) == 0 ) {
 sParam = rtmpt_get_amf_param ( tvb , offset + soff , 3 , "code" ) ;
 tp -> isresponse = TRUE ;
 }
 if ( tp -> txid != 0 && tp -> otherframe == 0 ) {
 tp -> otherframe = GPOINTER_TO_INT ( wmem_tree_lookup32 ( rconv -> txids [ cdir ^ 1 ] , tp -> txid ) ) ;
 if ( tp -> otherframe ) {
 RTMPT_DEBUG ( "got otherframe=%d\n" , tp -> otherframe ) ;
 }
 }
 }
 if ( sFunc ) {
 if ( sParam ) {
 return wmem_strdup_printf ( wmem_packet_scope ( ) , "%s('%s')" , sFunc , sParam ) ;
 }
 else {
 return wmem_strdup_printf ( wmem_packet_scope ( ) , "%s()" , sFunc ) ;
 }
 }
 }
 return NULL ;
 }