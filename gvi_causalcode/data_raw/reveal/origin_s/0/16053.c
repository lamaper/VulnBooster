static void h264_close_context ( PayloadContext * data ) {

 for ( ii = 0 ;
 ii < 32 ;
 ii ++ ) {
 if ( data -> packet_types_received [ ii ] ) av_log ( NULL , AV_LOG_DEBUG , "Received %d packets of type %d\n" , data -> packet_types_received [ ii ] , ii ) ;
 }
