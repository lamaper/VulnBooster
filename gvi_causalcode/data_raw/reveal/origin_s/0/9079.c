static void ber_add_syntax_name ( gpointer key , gpointer value _U_ , gpointer user_data ) {
 guint * i = ( guint * ) user_data ;
 if ( * i < MAX_SYNTAX_NAMES ) {
 syntax_names [ * i ] . value = * i ;
 syntax_names [ * i ] . strptr = ( const gchar * ) key ;
 ( * i ) ++ ;
 }
 }