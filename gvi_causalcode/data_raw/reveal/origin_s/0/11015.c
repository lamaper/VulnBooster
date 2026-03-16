static gpg_err_code_t octet_string_from_mpi ( unsigned char * * r_frame , void * space , gcry_mpi_t value , size_t nbytes ) {
 gpg_err_code_t rc ;
 size_t nframe , noff , n ;
 unsigned char * frame ;
 if ( ! r_frame == ! space ) return GPG_ERR_INV_ARG ;
 if ( r_frame ) * r_frame = NULL ;
 rc = gcry_err_code ( gcry_mpi_print ( GCRYMPI_FMT_USG , NULL , 0 , & nframe , value ) ) ;
 if ( rc ) return rc ;
 if ( nframe > nbytes ) return GPG_ERR_TOO_LARGE ;
 noff = ( nframe < nbytes ) ? nbytes - nframe : 0 ;
 n = nframe + noff ;
 if ( space ) frame = space ;
 else {
 frame = mpi_is_secure ( value ) ? gcry_malloc_secure ( n ) : gcry_malloc ( n ) ;
 if ( ! frame ) {
 rc = gpg_err_code_from_syserror ( ) ;
 return rc ;
 }
 }
 if ( noff ) memset ( frame , 0 , noff ) ;
 nframe += noff ;
 rc = gcry_err_code ( gcry_mpi_print ( GCRYMPI_FMT_USG , frame + noff , nframe - noff , NULL , value ) ) ;
 if ( rc ) {
 gcry_free ( frame ) ;
 return rc ;
 }
 if ( r_frame ) * r_frame = frame ;
 return 0 ;
 }