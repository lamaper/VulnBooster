static void decode_power_profile_id ( gchar * s , guint8 id ) {
 if ( id == 0 ) {
 g_snprintf ( s , ITEM_LABEL_LENGTH , "%d (All)" , id ) ;
 }
 else {
 g_snprintf ( s , ITEM_LABEL_LENGTH , "%d" , id ) ;
 }
 }