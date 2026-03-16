gcry_mpi_point_t make_point ( const char * x , const char * y , const char * z ) {
 gcry_mpi_point_t point ;
 point = gcry_mpi_point_new ( 0 ) ;
 gcry_mpi_point_snatch_set ( point , hex2mpi ( x ) , hex2mpi ( y ) , hex2mpi ( z ) ) ;
 return point ;
 }