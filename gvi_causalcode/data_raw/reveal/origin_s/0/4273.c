static void decode_color_xy ( gchar * s , guint16 value ) {
 g_snprintf ( s , ITEM_LABEL_LENGTH , "%.4lf" , value / 65535.0 ) ;
 return ;
 }