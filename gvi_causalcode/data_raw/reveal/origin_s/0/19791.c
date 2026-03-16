static void func_decode_delayinminute ( gchar * s , guint16 value ) {
 if ( value == 0 ) {
 g_snprintf ( s , ITEM_LABEL_LENGTH , "%d minutes (Not permitted)" , value ) ;
 }
 else {
 g_snprintf ( s , ITEM_LABEL_LENGTH , "%d minutes" , value ) ;
 }
 }