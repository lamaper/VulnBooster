struct evhttp_connection * evhttp_request_get_connection ( struct evhttp_request * req ) {
 return req -> evcon ;
 }