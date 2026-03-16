void retry_outgoing ( outgoing_t * outgoing ) {
 outgoing -> timeout += 5 ;
 if ( outgoing -> timeout < mintimeout ) {
 outgoing -> timeout = mintimeout ;
 }
 if ( outgoing -> timeout > maxtimeout ) {
 outgoing -> timeout = maxtimeout ;
 }
 if ( outgoing -> event ) {
 event_del ( outgoing -> event ) ;
 }
 outgoing -> event = new_event ( ) ;
 outgoing -> event -> handler = ( event_handler_t ) setup_outgoing_connection ;
 outgoing -> event -> time = now + outgoing -> timeout ;
 outgoing -> event -> data = outgoing ;
 event_add ( outgoing -> event ) ;
 ifdebug ( CONNECTIONS ) logger ( LOG_NOTICE , "Trying to re-establish outgoing connection in %d seconds" , outgoing -> timeout ) ;
 }