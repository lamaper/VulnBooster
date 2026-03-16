void mpi_swap ( MPI a , MPI b ) {
 struct gcry_mpi tmp ;
 tmp = * a ;
 * a = * b ;
 * b = tmp ;
 }