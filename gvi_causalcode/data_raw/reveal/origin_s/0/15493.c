static int raw_decode ( char * packet , int len , struct query * q , int dns_fd , int tun_fd ) {
 int raw_user ;
 if ( len < RAW_HDR_LEN ) return 0 ;
 if ( memcmp ( packet , raw_header , RAW_HDR_IDENT_LEN ) ) return 0 ;
 raw_user = RAW_HDR_GET_USR ( packet ) ;
 switch ( RAW_HDR_GET_CMD ( packet ) ) {
 case RAW_HDR_CMD_LOGIN : handle_raw_login ( & packet [ RAW_HDR_LEN ] , len - RAW_HDR_LEN , q , dns_fd , raw_user ) ;
 break ;
 case RAW_HDR_CMD_DATA : handle_raw_data ( & packet [ RAW_HDR_LEN ] , len - RAW_HDR_LEN , q , dns_fd , tun_fd , raw_user ) ;
 break ;
 case RAW_HDR_CMD_PING : handle_raw_ping ( q , dns_fd , raw_user ) ;
 break ;
 default : warnx ( "Unhandled raw command %02X from user %d" , RAW_HDR_GET_CMD ( packet ) , raw_user ) ;
 break ;
 }
 return 1 ;
 }