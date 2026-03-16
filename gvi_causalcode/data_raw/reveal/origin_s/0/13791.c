static void btatt_handle_prompt ( packet_info * pinfo , gchar * result ) {
 guint16 * value_data ;
 value_data = ( guint16 * ) p_get_proto_data ( pinfo -> pool , pinfo , proto_btatt , PROTO_DATA_BTATT_HANDLE ) ;
 if ( value_data ) g_snprintf ( result , MAX_DECODE_AS_PROMPT_LEN , "ATT Handle 0x%04x as" , ( guint ) * value_data ) ;
 else g_snprintf ( result , MAX_DECODE_AS_PROMPT_LEN , "Unknown ATT Handle" ) ;
 }