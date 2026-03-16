static gcry_mpi_t mpi_read_from_buffer ( const unsigned char * buffer , unsigned * ret_nread , int secure ) {
 int i , j ;
 unsigned int nbits , nbytes , nlimbs , nread = 0 ;
 mpi_limb_t a ;
 gcry_mpi_t val = MPI_NULL ;
 if ( * ret_nread < 2 ) goto leave ;
 nbits = buffer [ 0 ] << 8 | buffer [ 1 ] ;
 if ( nbits > MAX_EXTERN_MPI_BITS ) {
 goto leave ;
 }
 buffer += 2 ;
 nread = 2 ;
 nbytes = ( nbits + 7 ) / 8 ;
 nlimbs = ( nbytes + BYTES_PER_MPI_LIMB - 1 ) / BYTES_PER_MPI_LIMB ;
 val = secure ? mpi_alloc_secure ( nlimbs ) : mpi_alloc ( nlimbs ) ;
 i = BYTES_PER_MPI_LIMB - nbytes % BYTES_PER_MPI_LIMB ;
 i %= BYTES_PER_MPI_LIMB ;
 j = val -> nlimbs = nlimbs ;
 val -> sign = 0 ;
 for ( ;
 j > 0 ;
 j -- ) {
 a = 0 ;
 for ( ;
 i < BYTES_PER_MPI_LIMB ;
 i ++ ) {
 if ( ++ nread > * ret_nread ) {
 mpi_free ( val ) ;
 val = NULL ;
 goto leave ;
 }
 a <<= 8 ;
 a |= * buffer ++ ;
 }
 i = 0 ;
 val -> d [ j - 1 ] = a ;
 }
 leave : * ret_nread = nread ;
 return val ;
 }