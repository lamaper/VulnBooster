void dtls1_start_timer ( SSL * s ) {

 memset ( & s -> d1 -> next_timeout , 0 , sizeof ( s -> d1 -> next_timeout ) ) ;
 return ;
 }

 s -> d1 -> timeout_duration = 1 ;
 }
 get_current_time ( & ( s -> d1 -> next_timeout ) ) ;
 s -> d1 -> next_timeout . tv_sec += s -> d1 -> timeout_duration ;
 BIO_ctrl ( SSL_get_rbio ( s ) , BIO_CTRL_DGRAM_SET_NEXT_TIMEOUT , 0 , & ( s -> d1 -> next_timeout ) ) ;
 }