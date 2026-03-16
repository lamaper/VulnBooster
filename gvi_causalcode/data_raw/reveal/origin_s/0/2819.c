static gboolean test_applemidi ( tvbuff_t * tvb , guint16 * command_p , gboolean conversation_established ) {
 * command_p = 0xffff ;
 if ( APPLEMIDI_PROTOCOL_SIGNATURE != tvb_get_ntohs ( tvb , 0 ) ) return FALSE ;
 * command_p = tvb_get_ntohs ( tvb , 2 ) ;
 if ( conversation_established ) {
 return TRUE ;
 }
 if ( ( APPLEMIDI_COMMAND_INVITATION == * command_p ) || ( APPLEMIDI_COMMAND_INVITATION_REJECTED == * command_p ) || ( APLLEMIDI_COMMAND_INVITATION_ACCEPTED == * command_p ) || ( APPLEMIDI_COMMAND_ENDSESSION == * command_p ) || ( APPLEMIDI_COMMAND_SYNCHRONIZATION == * command_p ) || ( APPLEMIDI_COMMAND_RECEIVER_FEEDBACK == * command_p ) || ( APPLEMIDI_COMMAND_BITRATE_RECEIVE_LIMIT == * command_p ) ) return TRUE ;
 return FALSE ;
 }