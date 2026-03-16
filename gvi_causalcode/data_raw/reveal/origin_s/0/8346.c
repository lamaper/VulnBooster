void evhttp_connection_set_closecb ( struct evhttp_connection * evcon , void ( * cb ) ( struct evhttp_connection * , void * ) , void * cbarg ) {
 evcon -> closecb = cb ;
 evcon -> closecb_arg = cbarg ;
 }