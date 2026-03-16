int doqueryex ( int opcode , associd_t associd , int auth , int qsize , const char * qdata , u_short * rstatus , int * rsize , const char * * rdata , int quiet ) {
 int res ;
 int done ;
 if ( ! havehost ) {
 fprintf ( stderr , "***No host open, use `host' command\n" ) ;
 return - 1 ;
 }
 done = 0 ;
 sequence ++ ;
 again : res = sendrequest ( opcode , associd , auth , qsize , qdata ) ;
 if ( res != 0 ) return res ;
 res = getresponse ( opcode , associd , rstatus , rsize , rdata , done ) ;
 if ( res > 0 ) {
 if ( ! done && ( res == ERR_TIMEOUT || res == ERR_INCOMPLETE ) ) {
 if ( res == ERR_INCOMPLETE ) {
 sequence ++ ;
 }
 done = 1 ;
 goto again ;
 }
 if ( ! quiet ) show_error_msg ( res , associd ) ;
 }
 return res ;
 }