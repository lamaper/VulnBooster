static int adb_send ( socket_handle_t sock , const char * adb_service ) {
 char buffer [ 4 ] ;
 gssize used_buffer_length ;
 gssize result ;
 size_t adb_service_length ;
 adb_service_length = strlen ( adb_service ) ;
 result = send ( sock , adb_service , ( int ) adb_service_length , 0 ) ;
 if ( result != ( gssize ) adb_service_length ) {
 errmsg_print ( "ERROR: Error while sending <%s> to ADB" , adb_service ) ;
 return EXIT_CODE_ERROR_WHILE_SENDING_ADB_PACKET_1 ;
 }
 used_buffer_length = 0 ;
 while ( used_buffer_length < 4 ) {
 result = recv ( sock , buffer + used_buffer_length , ( int ) ( sizeof ( buffer ) - used_buffer_length ) , 0 ) ;
 if ( result <= 0 ) {
 errmsg_print ( "ERROR: Broken socket connection while fetching reply status for <%s>" , adb_service ) ;
 return EXIT_CODE_ERROR_WHILE_RECEIVING_ADB_PACKET_STATUS ;
 }
 used_buffer_length += result ;
 }
 if ( memcmp ( buffer , "OKAY" , 4 ) ) {
 errmsg_print ( "ERROR: Error while receiving by ADB for <%s>" , adb_service ) ;
 return EXIT_CODE_ERROR_WHILE_RECEIVING_ADB_PACKET_DATA ;
 }
 return EXIT_CODE_SUCCESS ;
 }