gpg_err_code_t _gcry_ecc_ecdsa_sign ( gcry_mpi_t input , ECC_secret_key * skey , gcry_mpi_t r , gcry_mpi_t s , int flags , int hashalgo ) {
 gpg_err_code_t rc = 0 ;
 int extraloops = 0 ;
 gcry_mpi_t k , dr , sum , k_1 , x ;
 mpi_point_struct I ;
 gcry_mpi_t hash ;
 const void * abuf ;
 unsigned int abits , qbits ;
 mpi_ec_t ctx ;
 if ( DBG_CIPHER ) log_mpidump ( "ecdsa sign hash " , input ) ;
 qbits = mpi_get_nbits ( skey -> E . n ) ;
 rc = _gcry_dsa_normalize_hash ( input , & hash , qbits ) ;
 if ( rc ) return rc ;
 k = NULL ;
 dr = mpi_alloc ( 0 ) ;
 sum = mpi_alloc ( 0 ) ;
 k_1 = mpi_alloc ( 0 ) ;
 x = mpi_alloc ( 0 ) ;
 point_init ( & I ) ;
 ctx = _gcry_mpi_ec_p_internal_new ( skey -> E . model , skey -> E . dialect , 0 , skey -> E . p , skey -> E . a , skey -> E . b ) ;
 do {
 do {
 mpi_free ( k ) ;
 k = NULL ;
 if ( ( flags & PUBKEY_FLAG_RFC6979 ) && hashalgo ) {
 if ( ! mpi_is_opaque ( input ) ) {
 rc = GPG_ERR_CONFLICT ;
 goto leave ;
 }
 abuf = mpi_get_opaque ( input , & abits ) ;
 rc = _gcry_dsa_gen_rfc6979_k ( & k , skey -> E . n , skey -> d , abuf , ( abits + 7 ) / 8 , hashalgo , extraloops ) ;
 if ( rc ) goto leave ;
 extraloops ++ ;
 }
 else k = _gcry_dsa_gen_k ( skey -> E . n , GCRY_STRONG_RANDOM ) ;
 _gcry_mpi_ec_mul_point ( & I , k , & skey -> E . G , ctx ) ;
 if ( _gcry_mpi_ec_get_affine ( x , NULL , & I , ctx ) ) {
 if ( DBG_CIPHER ) log_debug ( "ecc sign: Failed to get affine coordinates\n" ) ;
 rc = GPG_ERR_BAD_SIGNATURE ;
 goto leave ;
 }
 mpi_mod ( r , x , skey -> E . n ) ;
 }
 while ( ! mpi_cmp_ui ( r , 0 ) ) ;
 mpi_mulm ( dr , skey -> d , r , skey -> E . n ) ;
 mpi_addm ( sum , hash , dr , skey -> E . n ) ;
 mpi_invm ( k_1 , k , skey -> E . n ) ;
 mpi_mulm ( s , k_1 , sum , skey -> E . n ) ;
 }
 while ( ! mpi_cmp_ui ( s , 0 ) ) ;
 if ( DBG_CIPHER ) {
 log_mpidump ( "ecdsa sign result r " , r ) ;
 log_mpidump ( "ecdsa sign result s " , s ) ;
 }
 leave : _gcry_mpi_ec_free ( ctx ) ;
 point_free ( & I ) ;
 mpi_free ( x ) ;
 mpi_free ( k_1 ) ;
 mpi_free ( sum ) ;
 mpi_free ( dr ) ;
 mpi_free ( k ) ;
 if ( hash != input ) mpi_free ( hash ) ;
 return rc ;
 }