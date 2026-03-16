void http_post_cb ( struct evhttp_request * req , void * arg ) {
 struct evbuffer * evb ;
 event_debug ( ( "%s: called\n" , __func__ ) ) ;
 if ( req -> type != EVHTTP_REQ_POST ) {
 fprintf ( stdout , "FAILED (post type)\n" ) ;
 exit ( 1 ) ;
 }
 if ( EVBUFFER_LENGTH ( req -> input_buffer ) != strlen ( POST_DATA ) ) {
 fprintf ( stdout , "FAILED (length: %zu vs %zu)\n" , EVBUFFER_LENGTH ( req -> input_buffer ) , strlen ( POST_DATA ) ) ;
 exit ( 1 ) ;
 }
 if ( memcmp ( EVBUFFER_DATA ( req -> input_buffer ) , POST_DATA , strlen ( POST_DATA ) ) ) {
 fprintf ( stdout , "FAILED (data)\n" ) ;
 fprintf ( stdout , "Got :%s\n" , EVBUFFER_DATA ( req -> input_buffer ) ) ;
 fprintf ( stdout , "Want:%s\n" , POST_DATA ) ;
 exit ( 1 ) ;
 }
 evb = evbuffer_new ( ) ;
 evbuffer_add_printf ( evb , "This is funny" ) ;
 evhttp_send_reply ( req , HTTP_OK , "Everything is fine" , evb ) ;
 evbuffer_free ( evb ) ;
 }