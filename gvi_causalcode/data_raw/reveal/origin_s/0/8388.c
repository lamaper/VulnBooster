void evbuffer_setcb ( struct evbuffer * buffer , void ( * cb ) ( struct evbuffer * , size_t , size_t , void * ) , void * cbarg ) {
 buffer -> cb = cb ;
 buffer -> cbarg = cbarg ;
 }