GHashTable * prplcb_ui_info ( ) {
 static GHashTable * ret ;
 if ( ret == NULL ) {
 ret = g_hash_table_new ( g_str_hash , g_str_equal ) ;
 g_hash_table_insert ( ret , "name" , "BitlBee" ) ;
 g_hash_table_insert ( ret , "version" , BITLBEE_VERSION ) ;
 }
 return ret ;
 }