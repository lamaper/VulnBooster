static void server_request_free_answers ( struct server_request * req ) {
 struct server_reply_item * victim , * next , * * list ;
 int i ;
 for ( i = 0 ;
 i < 3 ;
 ++ i ) {
 if ( i == 0 ) list = & req -> answer ;
 else if ( i == 1 ) list = & req -> authority ;
 else list = & req -> additional ;
 victim = * list ;
 while ( victim ) {
 next = victim -> next ;
 free ( victim -> name ) ;
 if ( victim -> data ) free ( victim -> data ) ;
 free ( victim ) ;
 victim = next ;
 }
 * list = NULL ;
 }
 }