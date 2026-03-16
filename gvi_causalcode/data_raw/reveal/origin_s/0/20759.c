int evdns_server_request_add_reply ( struct evdns_server_request * _req , int section , const char * name , int type , int class , int ttl , int datalen , int is_name , const char * data ) {
 struct server_request * req = TO_SERVER_REQUEST ( _req ) ;
 struct server_reply_item * * itemp , * item ;
 int * countp ;
 if ( req -> response ) return ( - 1 ) ;
 switch ( section ) {
 case EVDNS_ANSWER_SECTION : itemp = & req -> answer ;
 countp = & req -> n_answer ;
 break ;
 case EVDNS_AUTHORITY_SECTION : itemp = & req -> authority ;
 countp = & req -> n_authority ;
 break ;
 case EVDNS_ADDITIONAL_SECTION : itemp = & req -> additional ;
 countp = & req -> n_additional ;
 break ;
 default : return ( - 1 ) ;
 }
 while ( * itemp ) {
 itemp = & ( ( * itemp ) -> next ) ;
 }
 item = malloc ( sizeof ( struct server_reply_item ) ) ;
 if ( ! item ) return - 1 ;
 item -> next = NULL ;
 if ( ! ( item -> name = strdup ( name ) ) ) {
 free ( item ) ;
 return - 1 ;
 }
 item -> type = type ;
 item -> dns_question_class = class ;
 item -> ttl = ttl ;
 item -> is_name = is_name != 0 ;
 item -> datalen = 0 ;
 item -> data = NULL ;
 if ( data ) {
 if ( item -> is_name ) {
 if ( ! ( item -> data = strdup ( data ) ) ) {
 free ( item -> name ) ;
 free ( item ) ;
 return - 1 ;
 }
 item -> datalen = ( u16 ) - 1 ;
 }
 else {
 if ( ! ( item -> data = malloc ( datalen ) ) ) {
 free ( item -> name ) ;
 free ( item ) ;
 return - 1 ;
 }
 item -> datalen = datalen ;
 memcpy ( item -> data , data , datalen ) ;
 }
 }
 * itemp = item ;
 ++ ( * countp ) ;
 return 0 ;
 }