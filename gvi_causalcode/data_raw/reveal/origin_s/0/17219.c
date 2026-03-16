static void decode_zcl_ota_curr_time ( gchar * s , guint32 value ) {
 if ( value == ZBEE_ZCL_OTA_TIME_NOW ) {
 g_snprintf ( s , ITEM_LABEL_LENGTH , "Now" ) ;
 }
 else {
 gchar * tmp ;
 value += ZBEE_ZCL_NSTIME_UTC_OFFSET ;
 tmp = abs_time_secs_to_str ( NULL , value , ABSOLUTE_TIME_LOCAL , 1 ) ;
 g_snprintf ( s , ITEM_LABEL_LENGTH , "%s" , tmp ) ;
 wmem_free ( NULL , tmp ) ;
 }
 return ;
 }