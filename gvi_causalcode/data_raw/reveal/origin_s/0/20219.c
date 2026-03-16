void evhttp_send_reply_chunk ( struct evhttp_request * req , struct evbuffer * databuf ) {
 struct evhttp_connection * evcon = req -> evcon ;
 if ( evcon == NULL ) return ;
 if ( req -> chunked ) {
 evbuffer_add_printf ( evcon -> output_buffer , "%x\r\n" , ( unsigned ) EVBUFFER_LENGTH ( databuf ) ) ;
 }
 evbuffer_add_buffer ( evcon -> output_buffer , databuf ) ;
 if ( req -> chunked ) {
 evbuffer_add ( evcon -> output_buffer , "\r\n" , 2 ) ;
 }
 evhttp_write_buffer ( evcon , NULL , NULL ) ;
 }