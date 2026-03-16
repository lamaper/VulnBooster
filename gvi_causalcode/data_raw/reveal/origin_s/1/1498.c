void evhttp_send_reply_chunk ( struct evhttp_request * req , struct evbuffer * databuf ) {
 if ( req -> chunked ) {
 evbuffer_add_printf ( req -> evcon -> output_buffer , "%x\r\n" , ( unsigned ) EVBUFFER_LENGTH ( databuf ) ) ;
 }
 evbuffer_add_buffer ( req -> evcon -> output_buffer , databuf ) ;
 if ( req -> chunked ) {
 evbuffer_add ( req -> evcon -> output_buffer , "\r\n" , 2 ) ;
 }
 evhttp_write_buffer ( req -> evcon , NULL , NULL ) ;
 }