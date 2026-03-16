static int get_and_cmp_mpi ( const char * name , const char * mpistring , const char * desc , gcry_ctx_t ctx ) {
 gcry_mpi_t mpi ;
 mpi = gcry_mpi_ec_get_mpi ( name , ctx , 1 ) ;
 if ( ! mpi ) {
 fail ( "error getting parameter '%s' of curve '%s'\n" , name , desc ) ;
 return 1 ;
 }
 if ( debug ) print_mpi ( name , mpi ) ;
 if ( cmp_mpihex ( mpi , mpistring ) ) {
 fail ( "parameter '%s' of curve '%s' does not match\n" , name , desc ) ;
 gcry_mpi_release ( mpi ) ;
 return 1 ;
 }
 gcry_mpi_release ( mpi ) ;
 return 0 ;
 }