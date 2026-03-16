void evhttp_set_gencb ( struct evhttp * http , void ( * cb ) ( struct evhttp_request * , void * ) , void * cbarg ) {
 http -> gencb = cb ;
 http -> gencbarg = cbarg ;
 }