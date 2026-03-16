static void last_msg_dec_owns ( GSList * list ) {
 LAST_MSG_REC * rec ;
 while ( list != NULL ) {
 rec = list -> data ;
 if ( rec -> own ) rec -> own -- ;
 list = list -> next ;
 }
 }