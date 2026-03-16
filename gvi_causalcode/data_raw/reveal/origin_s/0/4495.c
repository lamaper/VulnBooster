static void decode_power_conf_frequency ( gchar * s , guint32 value ) {
 if ( value == 0x00 ) g_snprintf ( s , ITEM_LABEL_LENGTH , "Frequency too low to be measured (or DC supply)" ) ;
 else if ( value == 0xfe ) g_snprintf ( s , ITEM_LABEL_LENGTH , "Frequency too high to be measured" ) ;
 else if ( value == 0xff ) g_snprintf ( s , ITEM_LABEL_LENGTH , "Frequency could not be measured" ) ;
 else g_snprintf ( s , ITEM_LABEL_LENGTH , "%d [Hz]" , value * 2 ) ;
 return ;
 }