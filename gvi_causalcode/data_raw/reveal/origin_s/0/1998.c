static void end_ssl ( ) {

 free_vio_ssl_acceptor_fd ( ssl_acceptor_fd ) ;
 ssl_acceptor_fd = 0 ;
 }
