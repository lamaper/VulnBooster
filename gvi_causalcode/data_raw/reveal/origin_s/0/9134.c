static const char * socket_activation_validate_opts ( const char * device , const char * sockpath , const char * address , const char * port ) {
 if ( device != NULL ) {
 return "NBD device can't be set when using socket activation" ;
 }
 if ( sockpath != NULL ) {
 return "Unix socket can't be set when using socket activation" ;
 }
 if ( address != NULL ) {
 return "The interface can't be set when using socket activation" ;
 }
 if ( port != NULL ) {
 return "TCP port number can't be set when using socket activation" ;
 }
 return NULL ;
 }