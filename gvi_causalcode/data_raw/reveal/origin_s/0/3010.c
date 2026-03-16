static void dissect_rtmpt ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , rtmpt_conv_t * rconv , int cdir , rtmpt_packet_t * tp ) {
 gint offset = 0 ;
 gchar * sDesc = NULL ;
 gint deschasopcode = FALSE ;
 gboolean haveETS = FALSE ;
 guint32 iBodyOffset = 0 ;
 guint32 iBodyRemain = 0 ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "RTMP" ) ;
 RTMPT_DEBUG ( "Dissect: frame=%u visited=%d len=%d tree=%p\n" , pinfo -> num , pinfo -> fd -> flags . visited , tvb_reported_length_remaining ( tvb , offset ) , tree ) ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 if ( tvb_reported_length_remaining ( tvb , offset ) < 1 ) return ;
 if ( tp -> id <= RTMPT_ID_MAX ) {
 if ( tp -> fmt < 3 && tvb_reported_length_remaining ( tvb , offset ) >= tp -> bhlen + 3 && tvb_get_ntoh24 ( tvb , offset + tp -> bhlen ) == 0xffffff ) {
 haveETS = TRUE ;
 }
 iBodyOffset = offset + tp -> bhlen + tp -> mhlen ;
 iBodyRemain = tvb_reported_length_remaining ( tvb , iBodyOffset ) ;
 if ( tp -> cmd == RTMPT_TYPE_CHUNK_SIZE && tp -> len >= 4 && iBodyRemain >= 4 ) {
 guint32 newchunksize = tvb_get_ntohl ( tvb , iBodyOffset ) ;
 if ( newchunksize < rtmpt_max_packet_size ) {
 wmem_tree_insert32 ( rconv -> chunksize [ cdir ] , tp -> lastseq , GINT_TO_POINTER ( newchunksize ) ) ;
 }
 }
 if ( ! PINFO_FD_VISITED ( pinfo ) ) {
 if ( tp -> cmd == RTMPT_TYPE_COMMAND_AMF0 || tp -> cmd == RTMPT_TYPE_COMMAND_AMF3 || tp -> cmd == RTMPT_TYPE_DATA_AMF0 || tp -> cmd == RTMPT_TYPE_DATA_AMF3 ) {
 guint32 soff = 0 ;
 if ( tp -> cmd == RTMPT_TYPE_COMMAND_AMF3 || tp -> cmd == RTMPT_TYPE_DATA_AMF3 ) {
 soff = 1 ;
 }
 tp -> txid = rtmpt_get_amf_txid ( tvb , iBodyOffset + soff ) ;
 if ( tp -> txid != 0 ) {
 RTMPT_DEBUG ( "got txid=%d\n" , tp -> txid ) ;
 wmem_tree_insert32 ( rconv -> txids [ cdir ] , tp -> txid , GINT_TO_POINTER ( pinfo -> num ) ) ;
 }
 }
 }
 }
 if ( tp -> id <= RTMPT_ID_MAX ) {
 sDesc = rtmpt_get_packet_desc ( tvb , iBodyOffset , iBodyRemain , rconv , cdir , tp , & deschasopcode ) ;
 }
 if ( tp -> id > RTMPT_ID_MAX ) {
 col_append_sep_fstr ( pinfo -> cinfo , COL_INFO , "|" , "%s" , val_to_str ( tp -> id , rtmpt_handshake_vals , "Unknown (0x%01x)" ) ) ;
 col_set_fence ( pinfo -> cinfo , COL_INFO ) ;
 }
 else if ( sDesc ) {
 col_append_sep_fstr ( pinfo -> cinfo , COL_INFO , "|" , "%s" , sDesc ) ;
 col_set_fence ( pinfo -> cinfo , COL_INFO ) ;
 }
 else {
 col_append_sep_fstr ( pinfo -> cinfo , COL_INFO , "|" , "%s" , val_to_str ( tp -> cmd , rtmpt_opcode_vals , "Unknown (0x%01x)" ) ) ;
 col_set_fence ( pinfo -> cinfo , COL_INFO ) ;
 }
 if ( tree ) {
 proto_tree * rtmpt_tree = NULL ;
 proto_tree * rtmptroot_tree = NULL ;
 proto_item * ti ;
 ti = proto_tree_add_item ( tree , proto_rtmpt , tvb , offset , - 1 , ENC_NA ) ;
 if ( tp -> id > RTMPT_ID_MAX ) {
 proto_item_append_text ( ti , " (%s)" , val_to_str ( tp -> id , rtmpt_handshake_vals , "Unknown (0x%01x)" ) ) ;
 rtmptroot_tree = proto_item_add_subtree ( ti , ett_rtmpt ) ;
 rtmpt_tree = proto_tree_add_subtree ( rtmptroot_tree , tvb , offset , - 1 , ett_rtmpt_handshake , NULL , val_to_str ( tp -> id , rtmpt_handshake_vals , "Unknown (0x%01x)" ) ) ;
 if ( tp -> id == RTMPT_TYPE_HANDSHAKE_1 ) {
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_handshake_c0 , tvb , 0 , 1 , ENC_NA ) ;
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_handshake_c1 , tvb , 1 , 1536 , ENC_NA ) ;
 }
 else if ( tp -> id == RTMPT_TYPE_HANDSHAKE_2 ) {
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_handshake_s0 , tvb , 0 , 1 , ENC_NA ) ;
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_handshake_s1 , tvb , 1 , 1536 , ENC_NA ) ;
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_handshake_s2 , tvb , 1537 , 1536 , ENC_NA ) ;
 }
 else if ( tp -> id == RTMPT_TYPE_HANDSHAKE_3 ) {
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_handshake_c2 , tvb , 0 , 1536 , ENC_NA ) ;
 }
 return ;
 }
 if ( sDesc && deschasopcode ) {
 proto_item_append_text ( ti , " (%s)" , sDesc ) ;
 }
 else if ( sDesc ) {
 proto_item_append_text ( ti , " (%s %s)" , val_to_str ( tp -> cmd , rtmpt_opcode_vals , "Unknown (0x%01x)" ) , sDesc ) ;
 }
 else {
 proto_item_append_text ( ti , " (%s)" , val_to_str ( tp -> cmd , rtmpt_opcode_vals , "Unknown (0x%01x)" ) ) ;
 }
 rtmptroot_tree = proto_item_add_subtree ( ti , ett_rtmpt ) ;
 if ( tp -> otherframe != 0 ) {
 proto_tree_add_uint ( rtmptroot_tree , tp -> isresponse ? hf_rtmpt_function_response : hf_rtmpt_function_call , tvb , offset , tp -> bhlen + tp -> mhlen + tp -> len , tp -> otherframe ) ;
 }
 rtmpt_tree = proto_tree_add_subtree ( rtmptroot_tree , tvb , offset , tp -> bhlen + tp -> mhlen , ett_rtmpt_header , NULL , RTMPT_TEXT_RTMP_HEADER ) ;
 if ( tp -> fmt <= 3 ) proto_tree_add_item ( rtmpt_tree , hf_rtmpt_header_format , tvb , offset + 0 , 1 , ENC_BIG_ENDIAN ) ;
 if ( tp -> fmt <= 3 ) proto_tree_add_item ( rtmpt_tree , hf_rtmpt_header_csid , tvb , offset + 0 , tp -> bhlen , ENC_BIG_ENDIAN ) ;
 if ( tp -> fmt <= 2 ) {
 if ( tp -> fmt > 0 ) {
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_header_timestamp_delta , tvb , offset + tp -> bhlen , 3 , ENC_BIG_ENDIAN ) ;
 }
 else {
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_header_timestamp , tvb , offset + tp -> bhlen , 3 , ENC_BIG_ENDIAN ) ;
 }
 if ( haveETS ) {
 proto_tree_add_item ( rtmpt_tree , hf_rtmpt_header_ets , tvb , offset + tp -> bhlen + tp -> mhlen - 4 , 4 , ENC_BIG_ENDIAN ) ;
 }
 }
 if ( ( tp -> fmt > 0 && ! haveETS ) || tp -> fmt == 3 ) {
 proto_tree_add_uint_format_value ( rtmpt_tree , hf_rtmpt_header_timestamp , tvb , offset + tp -> bhlen , 0 , tp -> ts , "%d (calculated)" , tp -> ts ) ;
 }
 if ( tp -> fmt <= 1 ) proto_tree_add_item ( rtmpt_tree , hf_rtmpt_header_body_size , tvb , offset + tp -> bhlen + 3 , 3 , ENC_BIG_ENDIAN ) ;
 if ( tp -> fmt <= 1 ) proto_tree_add_item ( rtmpt_tree , hf_rtmpt_header_typeid , tvb , offset + tp -> bhlen + 6 , 1 , ENC_BIG_ENDIAN ) ;
 if ( tp -> fmt <= 0 ) proto_tree_add_item ( rtmpt_tree , hf_rtmpt_header_streamid , tvb , offset + tp -> bhlen + 7 , 4 , ENC_LITTLE_ENDIAN ) ;
 if ( tp -> len == 0 ) return ;
 offset = iBodyOffset ;
 rtmpt_tree = proto_tree_add_subtree ( rtmptroot_tree , tvb , offset , - 1 , ett_rtmpt_body , NULL , RTMPT_TEXT_RTMP_BODY ) ;
 switch ( tp -> cmd ) {
 case RTMPT_TYPE_CHUNK_SIZE : case RTMPT_TYPE_ABORT_MESSAGE : case RTMPT_TYPE_ACKNOWLEDGEMENT : case RTMPT_TYPE_UCM : case RTMPT_TYPE_WINDOW : case RTMPT_TYPE_PEER_BANDWIDTH : dissect_rtmpt_body_scm ( tvb , offset , rtmpt_tree , tp -> cmd ) ;
 break ;
 case RTMPT_TYPE_COMMAND_AMF0 : case RTMPT_TYPE_DATA_AMF0 : dissect_rtmpt_body_command ( tvb , offset , rtmpt_tree , FALSE ) ;
 break ;
 case RTMPT_TYPE_COMMAND_AMF3 : case RTMPT_TYPE_DATA_AMF3 : dissect_rtmpt_body_command ( tvb , offset , rtmpt_tree , TRUE ) ;
 break ;
 case RTMPT_TYPE_AUDIO_DATA : dissect_rtmpt_body_audio ( tvb , offset , rtmpt_tree ) ;
 break ;
 case RTMPT_TYPE_VIDEO_DATA : dissect_rtmpt_body_video ( tvb , offset , rtmpt_tree ) ;
 break ;
 case RTMPT_TYPE_AGGREGATE : dissect_rtmpt_body_aggregate ( tvb , offset , rtmpt_tree ) ;
 break ;
 }
 }
 }