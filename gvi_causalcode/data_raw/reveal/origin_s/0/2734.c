void evhttp_connection_set_timeout ( struct evhttp_connection * evcon , int timeout_in_secs ) {
 evcon -> timeout = timeout_in_secs ;
 }