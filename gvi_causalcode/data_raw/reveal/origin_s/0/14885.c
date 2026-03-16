struct evhttp * evhttp_new ( struct event_base * base ) {
 struct evhttp * http = evhttp_new_object ( ) ;
 http -> base = base ;
 return ( http ) ;
 }