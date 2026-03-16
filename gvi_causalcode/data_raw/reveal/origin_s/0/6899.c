static FILE_DCC_REC * dcc_resume_find ( int type , const char * nick , int port ) {
 GSList * tmp ;
 for ( tmp = dcc_conns ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 FILE_DCC_REC * dcc = tmp -> data ;
 if ( dcc -> type == type && ! dcc_is_connected ( dcc ) && dcc -> port == port && g_ascii_strcasecmp ( dcc -> nick , nick ) == 0 ) return dcc ;
 }
 return NULL ;
 }