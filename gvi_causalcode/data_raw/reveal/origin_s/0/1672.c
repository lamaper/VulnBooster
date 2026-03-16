static char * purple_get_account_prpl_id ( account_t * acc ) {
 if ( g_strcmp0 ( acc -> prpl -> name , "oscar" ) == 0 ) {
 return ( g_ascii_isdigit ( acc -> user [ 0 ] ) ) ? "prpl-icq" : "prpl-aim" ;
 }
 return acc -> prpl -> data ;
 }