static gboolean protocol_is_alljoyn_message ( tvbuff_t * tvb , gint offset , gboolean is_ardp ) {
 gint length = tvb_captured_length ( tvb ) ;
 if ( length < offset + 1 ) return FALSE ;
 if ( ! is_ardp ) {
 if ( tvb_get_guint8 ( tvb , offset ) == 0 ) return TRUE ;
 if ( find_sasl_command ( tvb , offset ) != NULL ) return TRUE ;
 }
 if ( get_message_header_endianness ( tvb , offset ) == ENC_ALLJOYN_BAD_ENCODING ) return FALSE ;
 if ( ( length < offset + 2 ) || ( try_val_to_str ( tvb_get_guint8 ( tvb , offset + 1 ) , message_header_encoding_vals ) == NULL ) ) return FALSE ;
 return TRUE ;
 }