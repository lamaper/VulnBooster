enum message_read_status evhttp_parse_headers ( struct evhttp_request * req , struct evbuffer * buffer ) {
 char * line ;
 enum message_read_status status = MORE_DATA_EXPECTED ;
 struct evkeyvalq * headers = req -> input_headers ;
 while ( ( line = evbuffer_readline ( buffer ) ) != NULL ) {
 char * skey , * svalue ;
 if ( * line == '\0' ) {
 status = ALL_DATA_READ ;
 free ( line ) ;
 break ;
 }
 if ( * line == ' ' || * line == '\t' ) {
 if ( evhttp_append_to_last_header ( headers , line ) == - 1 ) goto error ;
 free ( line ) ;
 continue ;
 }
 svalue = line ;
 skey = strsep ( & svalue , ":" ) ;
 if ( svalue == NULL ) goto error ;
 svalue += strspn ( svalue , " " ) ;
 if ( evhttp_add_header ( headers , skey , svalue ) == - 1 ) goto error ;
 free ( line ) ;
 }
 return ( status ) ;
 error : free ( line ) ;
 return ( DATA_CORRUPTED ) ;
 }