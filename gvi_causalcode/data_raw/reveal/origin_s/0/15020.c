static void decode_price_in_cents ( gchar * s , guint32 value ) {
 g_snprintf ( s , ITEM_LABEL_LENGTH , "%d cents" , value ) ;
 }