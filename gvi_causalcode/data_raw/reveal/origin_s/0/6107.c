static const char * evhttp_method ( enum evhttp_cmd_type type ) {
 const char * method ;
 switch ( type ) {
 case EVHTTP_REQ_GET : method = "GET" ;
 break ;
 case EVHTTP_REQ_POST : method = "POST" ;
 break ;
 case EVHTTP_REQ_HEAD : method = "HEAD" ;
 break ;
 default : method = NULL ;
 break ;
 }
 return ( method ) ;
 }