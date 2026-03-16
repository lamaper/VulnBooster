void evhttp_set_timeout ( struct evhttp * http , int timeout_in_secs ) {
 http -> timeout = timeout_in_secs ;
 }