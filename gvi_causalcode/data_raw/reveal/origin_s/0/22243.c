static void decode_power_conf_voltage ( gchar * s , guint32 value ) {
 g_snprintf ( s , ITEM_LABEL_LENGTH , "%d.%d [V]" , value / 10 , value % 10 ) ;
 return ;
 }