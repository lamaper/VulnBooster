static void print_servers ( void ) {
 GSList * tmp ;
 for ( tmp = servers ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 SERVER_REC * rec = tmp -> data ;
 printformat ( NULL , NULL , MSGLEVEL_CRAP , TXT_SERVER_LIST , rec -> tag , rec -> connrec -> address , rec -> connrec -> port , rec -> connrec -> chatnet == NULL ? "" : rec -> connrec -> chatnet , rec -> connrec -> nick ) ;
 }
 }