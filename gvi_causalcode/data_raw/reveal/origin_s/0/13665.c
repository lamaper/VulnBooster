static void mpa_packetlist ( packet_info * pinfo , gint message_type ) {
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "MPA" ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "%d > %d %s" , pinfo -> srcport , pinfo -> destport , val_to_str ( message_type , mpa_messages , "Unknown %d" ) ) ;
 }