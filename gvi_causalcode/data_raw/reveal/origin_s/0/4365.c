static void * nbd_client_thread ( void * arg ) {
 char * device = arg ;
 off_t size ;
 uint16_t nbdflags ;
 QIOChannelSocket * sioc ;
 int fd ;
 int ret ;
 pthread_t show_parts_thread ;
 Error * local_error = NULL ;
 sioc = qio_channel_socket_new ( ) ;
 if ( qio_channel_socket_connect_sync ( sioc , saddr , & local_error ) < 0 ) {
 error_report_err ( local_error ) ;
 goto out ;
 }
 ret = nbd_receive_negotiate ( QIO_CHANNEL ( sioc ) , NULL , & nbdflags , NULL , NULL , NULL , & size , & local_error ) ;
 if ( ret < 0 ) {
 if ( local_error ) {
 error_report_err ( local_error ) ;
 }
 goto out_socket ;
 }
 fd = open ( device , O_RDWR ) ;
 if ( fd < 0 ) {
 error_report ( "Failed to open %s: %m" , device ) ;
 goto out_socket ;
 }
 ret = nbd_init ( fd , sioc , nbdflags , size , & local_error ) ;
 if ( ret < 0 ) {
 error_report_err ( local_error ) ;
 goto out_fd ;
 }
 pthread_create ( & show_parts_thread , NULL , show_parts , device ) ;
 if ( verbose ) {
 fprintf ( stderr , "NBD device %s is now connected to %s\n" , device , srcpath ) ;
 }
 else {
 dup2 ( STDOUT_FILENO , STDERR_FILENO ) ;
 }
 ret = nbd_client ( fd ) ;
 if ( ret ) {
 goto out_fd ;
 }
 close ( fd ) ;
 object_unref ( OBJECT ( sioc ) ) ;
 kill ( getpid ( ) , SIGTERM ) ;
 return ( void * ) EXIT_SUCCESS ;
 out_fd : close ( fd ) ;
 out_socket : object_unref ( OBJECT ( sioc ) ) ;
 out : kill ( getpid ( ) , SIGTERM ) ;
 return ( void * ) EXIT_FAILURE ;
 }