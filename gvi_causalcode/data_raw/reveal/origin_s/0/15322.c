gcry_err_code_t _gcry_ecc_get_param ( const char * name , gcry_mpi_t * pkey ) {
 gpg_err_code_t err ;
 unsigned int nbits ;
 elliptic_curve_t E ;
 mpi_ec_t ctx ;
 gcry_mpi_t g_x , g_y ;
 err = _gcry_ecc_fill_in_curve ( 0 , name , & E , & nbits ) ;
 if ( err ) return err ;
 g_x = mpi_new ( 0 ) ;
 g_y = mpi_new ( 0 ) ;
 ctx = _gcry_mpi_ec_p_internal_new ( 0 , E . p , E . a , NULL ) ;
 if ( _gcry_mpi_ec_get_affine ( g_x , g_y , & E . G , ctx ) ) log_fatal ( "ecc get param: Failed to get affine coordinates\n" ) ;
 _gcry_mpi_ec_free ( ctx ) ;
 _gcry_mpi_point_free_parts ( & E . G ) ;
 pkey [ 0 ] = E . p ;
 pkey [ 1 ] = E . a ;
 pkey [ 2 ] = E . b ;
 pkey [ 3 ] = _gcry_ecc_ec2os ( g_x , g_y , E . p ) ;
 pkey [ 4 ] = E . n ;
 pkey [ 5 ] = NULL ;
 mpi_free ( g_x ) ;
 mpi_free ( g_y ) ;
 return 0 ;
 }