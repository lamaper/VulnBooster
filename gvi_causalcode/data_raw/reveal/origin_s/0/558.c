static LAST_MSG_REC * last_msg_find ( GSList * list , const char * nick ) {
 while ( list != NULL ) {
 LAST_MSG_REC * rec = list -> data ;
 if ( g_ascii_strcasecmp ( rec -> nick , nick ) == 0 ) return rec ;
 list = list -> next ;
 }
 return NULL ;
 }