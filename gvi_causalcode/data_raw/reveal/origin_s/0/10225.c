void Curl_add_buffer_free ( Curl_send_buffer * buff ) {
 if ( buff ) free ( buff -> buffer ) ;
 free ( buff ) ;
 }