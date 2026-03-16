static void print_lookup_servers ( void ) {
 GSList * tmp ;
 for ( tmp = lookup_servers ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 SERVER_REC * rec = tmp -> data ;
 printformat ( NULL , NULL , MSGLEVEL_CRAP , TXT_SERVER_LOOKUP_LIST , rec -> tag , rec -> connrec -> address , rec -> connrec -> port , rec -> connrec -> chatnet == NULL ? "" : rec -> connrec -> chatnet , rec -> connrec -> nick ) ;
 }
 }