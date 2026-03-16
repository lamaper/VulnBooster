static void send_raw ( int fd , char * buf , int buflen , int user , int cmd , struct query * q ) {
 char packet [ 4096 ] ;
 int len ;
 len = MIN ( sizeof ( packet ) - RAW_HDR_LEN , buflen ) ;
 memcpy ( packet , raw_header , RAW_HDR_LEN ) ;
 if ( len ) {
 memcpy ( & packet [ RAW_HDR_LEN ] , buf , len ) ;
 }
 len += RAW_HDR_LEN ;
 packet [ RAW_HDR_CMD ] = cmd | ( user & 0x0F ) ;
 if ( debug >= 2 ) {
 fprintf ( stderr , "TX-raw: client %s, cmd %d, %d bytes\n" , format_addr ( & q -> from , q -> fromlen ) , cmd , len ) ;
 }
 sendto ( fd , packet , len , 0 , ( struct sockaddr * ) & q -> from , q -> fromlen ) ;
 }