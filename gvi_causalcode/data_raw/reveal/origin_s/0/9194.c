static void decrypt ( MPI output , MPI a , MPI b , ELG_secret_key * skey ) {
 MPI t1 , t2 , r ;
 unsigned int nbits = mpi_get_nbits ( skey -> p ) ;
 mpi_normalize ( a ) ;
 mpi_normalize ( b ) ;
 t1 = mpi_alloc_secure ( mpi_nlimb_hint_from_nbits ( nbits ) ) ;

 r = mpi_alloc ( mpi_nlimb_hint_from_nbits ( nbits ) ) ;
 randomize_mpi ( r , nbits , 0 ) ;
 mpi_powm ( t1 , r , skey -> x , skey -> p ) ;
 mpi_mulm ( t2 , a , r , skey -> p ) ;
 mpi_powm ( t2 , t2 , skey -> x , skey -> p ) ;
 mpi_invm ( t2 , t2 , skey -> p ) ;
 mpi_mulm ( t1 , t1 , t2 , skey -> p ) ;
 mpi_free ( r ) ;
 mpi_free ( t2 ) ;

 mpi_invm ( t1 , t1 , skey -> p ) ;


 log_mpidump ( "elg decrypted x= " , skey -> x ) ;
 log_mpidump ( "elg decrypted p= " , skey -> p ) ;
 log_mpidump ( "elg decrypted a= " , a ) ;
 log_mpidump ( "elg decrypted b= " , b ) ;
 log_mpidump ( "elg decrypted M= " , output ) ;
 }

 }