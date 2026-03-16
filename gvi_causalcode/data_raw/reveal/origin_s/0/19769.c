static void do_encrypt ( MPI a , MPI b , MPI input , ELG_public_key * pkey ) {
 MPI k ;
 k = gen_k ( pkey -> p , 1 ) ;
 mpi_powm ( a , pkey -> g , k , pkey -> p ) ;
 mpi_powm ( b , pkey -> y , k , pkey -> p ) ;
 mpi_mulm ( b , b , input , pkey -> p ) ;

 log_mpidump ( "elg encrypted y= " , pkey -> y ) ;
 log_mpidump ( "elg encrypted p= " , pkey -> p ) ;
 log_mpidump ( "elg encrypted k= " , k ) ;
 log_mpidump ( "elg encrypted M= " , input ) ;
 log_mpidump ( "elg encrypted a= " , a ) ;
 log_mpidump ( "elg encrypted b= " , b ) ;
 }

 }