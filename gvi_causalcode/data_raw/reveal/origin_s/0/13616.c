static void dissect_applemidi_common ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , guint16 command ) {
 guint16 seq_num ;
 guint8 count ;
 guint8 * name ;
 gint offset = 0 ;
 gint len ;
 gint string_size ;
 proto_tree * applemidi_tree ;
 proto_tree * applemidi_tree_seq_num ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , APPLEMIDI_DISSECTOR_SHORTNAME ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "%s" , val_to_str ( command , applemidi_commands , applemidi_unknown_command ) ) ;
 if ( tree ) {
 proto_item * ti ;
 ti = proto_tree_add_item ( tree , proto_applemidi , tvb , 0 , - 1 , ENC_NA ) ;
 applemidi_tree = proto_item_add_subtree ( ti , ett_applemidi ) ;
 proto_tree_add_item ( applemidi_tree , hf_applemidi_signature , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 proto_tree_add_item ( applemidi_tree , hf_applemidi_command , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 if ( ( APPLEMIDI_COMMAND_INVITATION == command ) || ( APPLEMIDI_COMMAND_INVITATION_REJECTED == command ) || ( APLLEMIDI_COMMAND_INVITATION_ACCEPTED == command ) || ( APPLEMIDI_COMMAND_ENDSESSION == command ) ) {
 proto_tree_add_item ( applemidi_tree , hf_applemidi_protocol_version , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( applemidi_tree , hf_applemidi_token , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( applemidi_tree , hf_applemidi_ssrc , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 len = tvb_reported_length ( tvb ) - offset ;
 if ( len > 0 ) {
 name = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset , len , ENC_UTF_8 | ENC_NA ) ;
 string_size = ( gint ) ( strlen ( name ) + 1 ) ;
 proto_tree_add_item ( applemidi_tree , hf_applemidi_name , tvb , offset , string_size , ENC_UTF_8 | ENC_NA ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , ": peer = \"%s\"" , name ) ;
 offset += string_size ;
 }
 }
 else if ( APPLEMIDI_COMMAND_SYNCHRONIZATION == command ) {
 proto_tree_add_item ( applemidi_tree , hf_applemidi_ssrc , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 count = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( applemidi_tree , hf_applemidi_count , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , ": count = %u" , count ) ;
 offset += 1 ;
 proto_tree_add_item ( applemidi_tree , hf_applemidi_padding , tvb , offset , 3 , ENC_BIG_ENDIAN ) ;
 offset += 3 ;
 proto_tree_add_item ( applemidi_tree , hf_applemidi_timestamp1 , tvb , offset , 8 , ENC_BIG_ENDIAN ) ;
 offset += 8 ;
 proto_tree_add_item ( applemidi_tree , hf_applemidi_timestamp2 , tvb , offset , 8 , ENC_BIG_ENDIAN ) ;
 offset += 8 ;
 proto_tree_add_item ( applemidi_tree , hf_applemidi_timestamp3 , tvb , offset , 8 , ENC_BIG_ENDIAN ) ;
 offset += 8 ;
 }
 else if ( APPLEMIDI_COMMAND_RECEIVER_FEEDBACK == command ) {
 proto_tree_add_item ( applemidi_tree , hf_applemidi_ssrc , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 ti = proto_tree_add_item ( applemidi_tree , hf_applemidi_sequence_num , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 applemidi_tree_seq_num = proto_item_add_subtree ( ti , ett_applemidi_seq_num ) ;
 seq_num = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_uint ( applemidi_tree_seq_num , hf_applemidi_rtp_sequence_num , tvb , offset , 2 , seq_num ) ;
 offset += 4 ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , ": seq = %u" , seq_num ) ;
 }
 else if ( APPLEMIDI_COMMAND_BITRATE_RECEIVE_LIMIT == command ) {
 proto_tree_add_item ( applemidi_tree , hf_applemidi_ssrc , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( applemidi_tree , hf_applemidi_rtp_bitrate_limit , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 }
 len = tvb_length_remaining ( tvb , offset ) ;
 if ( len > 0 ) {
 proto_tree_add_item ( applemidi_tree , hf_applemidi_unknown_data , tvb , offset , len , ENC_NA ) ;
 }
 }
 }