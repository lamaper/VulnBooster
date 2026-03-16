int message_search_msg ( struct message_search_context * ctx , struct istream * input , struct message_part * parts , const char * * error_r ) {
 char * error ;
 int ret ;
 T_BEGIN {
 ret = message_search_msg_real ( ctx , input , parts , error_r ) ;
 error = i_strdup ( * error_r ) ;
 }
 T_END ;
 * error_r = t_strdup ( error ) ;
 i_free ( error ) ;
 return ret ;
 }