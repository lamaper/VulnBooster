void evhttp_connection_set_retries ( struct evhttp_connection * evcon , int retry_max ) {
 evcon -> retry_max = retry_max ;
 }