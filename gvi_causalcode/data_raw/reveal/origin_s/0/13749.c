void _gcry_mpi_set_buffer ( gcry_mpi_t a , const void * buffer_arg , unsigned int nbytes , int sign ) {
 const unsigned char * buffer = ( const unsigned char * ) buffer_arg ;
 const unsigned char * p ;
 mpi_limb_t alimb ;
 int nlimbs ;
 int i ;
 if ( mpi_is_immutable ( a ) ) {
 mpi_immutable_failed ( ) ;
 return ;
 }
 nlimbs = ( nbytes + BYTES_PER_MPI_LIMB - 1 ) / BYTES_PER_MPI_LIMB ;
 RESIZE_IF_NEEDED ( a , nlimbs ) ;
 a -> sign = sign ;
 for ( i = 0 , p = buffer + nbytes - 1 ;
 p >= buffer + BYTES_PER_MPI_LIMB ;
 ) {

 alimb |= * p -- << 8 ;
 alimb |= * p -- << 16 ;
 alimb |= * p -- << 24 ;

 alimb |= ( mpi_limb_t ) * p -- << 8 ;
 alimb |= ( mpi_limb_t ) * p -- << 16 ;
 alimb |= ( mpi_limb_t ) * p -- << 24 ;
 alimb |= ( mpi_limb_t ) * p -- << 32 ;
 alimb |= ( mpi_limb_t ) * p -- << 40 ;
 alimb |= ( mpi_limb_t ) * p -- << 48 ;
 alimb |= ( mpi_limb_t ) * p -- << 56 ;

 }
 if ( p >= buffer ) {

 if ( p >= buffer ) alimb |= * p -- << 8 ;
 if ( p >= buffer ) alimb |= * p -- << 16 ;
 if ( p >= buffer ) alimb |= * p -- << 24 ;

 if ( p >= buffer ) alimb |= ( mpi_limb_t ) * p -- << 8 ;
 if ( p >= buffer ) alimb |= ( mpi_limb_t ) * p -- << 16 ;
 if ( p >= buffer ) alimb |= ( mpi_limb_t ) * p -- << 24 ;
 if ( p >= buffer ) alimb |= ( mpi_limb_t ) * p -- << 32 ;
 if ( p >= buffer ) alimb |= ( mpi_limb_t ) * p -- << 40 ;
 if ( p >= buffer ) alimb |= ( mpi_limb_t ) * p -- << 48 ;
 if ( p >= buffer ) alimb |= ( mpi_limb_t ) * p -- << 56 ;

 }
 a -> nlimbs = i ;
 gcry_assert ( i == nlimbs ) ;
 }