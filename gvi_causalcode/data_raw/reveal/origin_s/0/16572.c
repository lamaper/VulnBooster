static ssize_t qio_channel_websock_write_wire ( QIOChannelWebsock * ioc , Error * * errp ) {
 ssize_t ret ;
 ssize_t done = 0 ;
 if ( ! ioc -> ping_reply . offset ) {
 qio_channel_websock_encode ( ioc ) ;
 }
 else if ( ! ioc -> encoutput . offset ) {
 buffer_move_empty ( & ioc -> encoutput , & ioc -> ping_reply ) ;
 }
 while ( ioc -> encoutput . offset > 0 ) {
 ret = qio_channel_write ( ioc -> master , ( char * ) ioc -> encoutput . buffer , ioc -> encoutput . offset , errp ) ;
 if ( ret < 0 ) {
 if ( ret == QIO_CHANNEL_ERR_BLOCK && done > 0 ) {
 return done ;
 }
 else {
 return ret ;
 }
 }
 buffer_advance ( & ioc -> encoutput , ret ) ;
 done += ret ;
 }
 return done ;
 }