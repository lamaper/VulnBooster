static void send_version_response ( int fd , version_ack_t ack , uint32_t payload , int userid , struct query * q ) {
 char out [ 9 ] ;
 switch ( ack ) {
 case VERSION_ACK : strncpy ( out , "VACK" , sizeof ( out ) ) ;
 break ;
 case VERSION_NACK : strncpy ( out , "VNAK" , sizeof ( out ) ) ;
 break ;
 case VERSION_FULL : strncpy ( out , "VFUL" , sizeof ( out ) ) ;
 break ;
 }
 out [ 4 ] = ( ( payload >> 24 ) & 0xff ) ;
 out [ 5 ] = ( ( payload >> 16 ) & 0xff ) ;
 out [ 6 ] = ( ( payload >> 8 ) & 0xff ) ;
 out [ 7 ] = ( ( payload ) & 0xff ) ;
 out [ 8 ] = userid & 0xff ;
 write_dns ( fd , q , out , sizeof ( out ) , users [ userid ] . downenc ) ;
 }