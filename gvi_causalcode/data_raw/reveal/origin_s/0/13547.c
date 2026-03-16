static void decode_power_conf_batt_AHr ( gchar * s , guint32 value ) {
 g_snprintf ( s , ITEM_LABEL_LENGTH , "%d [mAHr]" , value * 10 ) ;
 return ;
 }