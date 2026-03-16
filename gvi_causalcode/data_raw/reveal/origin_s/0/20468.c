void evhttp_request_set_chunked_cb ( struct evhttp_request * req , void ( * cb ) ( struct evhttp_request * , void * ) ) {
 req -> chunk_cb = cb ;
 }