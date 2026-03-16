static MPI gen_k ( MPI p , int small_k ) {
 MPI k = mpi_alloc_secure ( 0 ) ;
 MPI temp = mpi_alloc ( mpi_get_nlimbs ( p ) ) ;
 MPI p_1 = mpi_copy ( p ) ;
 unsigned int orig_nbits = mpi_get_nbits ( p ) ;
 unsigned int nbits ;
 unsigned int nbytes ;
 char * rndbuf = NULL ;
 if ( small_k ) {
 nbits = wiener_map ( orig_nbits ) * 3 / 2 ;
 if ( nbits >= orig_nbits ) BUG ( ) ;
 }
 else nbits = orig_nbits ;
 nbytes = ( nbits + 7 ) / 8 ;
 if ( DBG_CIPHER ) log_debug ( "choosing a random k of %u bits" , nbits ) ;
 mpi_sub_ui ( p_1 , p , 1 ) ;
 for ( ;
 ;
 ) {
 if ( ! rndbuf || nbits < 32 ) {
 xfree ( rndbuf ) ;
 rndbuf = get_random_bits ( nbits , 1 , 1 ) ;
 }
 else {
 char * pp = get_random_bits ( 32 , 1 , 1 ) ;
 memcpy ( rndbuf , pp , 4 ) ;
 xfree ( pp ) ;
 }
 mpi_set_buffer ( k , rndbuf , nbytes , 0 ) ;
 for ( ;
 ;
 ) {
 if ( ! ( mpi_cmp ( k , p_1 ) < 0 ) ) {
 if ( DBG_CIPHER ) progress ( '+' ) ;
 break ;
 }
 if ( ! ( mpi_cmp_ui ( k , 0 ) > 0 ) ) {
 if ( DBG_CIPHER ) progress ( '-' ) ;
 break ;
 }
 if ( mpi_gcd ( temp , k , p_1 ) ) goto found ;
 mpi_add_ui ( k , k , 1 ) ;
 if ( DBG_CIPHER ) progress ( '.' ) ;
 }
 }
 found : xfree ( rndbuf ) ;
 if ( DBG_CIPHER ) progress ( '\n' ) ;
 mpi_free ( p_1 ) ;
 mpi_free ( temp ) ;
 return k ;
 }