static void basic_ec_math ( void ) {
 gpg_error_t err ;
 gcry_ctx_t ctx ;
 gcry_mpi_t P , A ;
 gcry_mpi_point_t G , Q ;
 gcry_mpi_t d ;
 gcry_mpi_t x , y , z ;
 wherestr = "basic_ec_math" ;
 show ( "checking basic math functions for EC\n" ) ;
 P = hex2mpi ( "0xfffffffffffffffffffffffffffffffeffffffffffffffff" ) ;
 A = hex2mpi ( "0xfffffffffffffffffffffffffffffffefffffffffffffffc" ) ;
 G = make_point ( "188DA80EB03090F67CBF20EB43A18800F4FF0AFD82FF1012" , "7192B95FFC8DA78631011ED6B24CDD573F977A11E794811" , "1" ) ;
 d = hex2mpi ( "D4EF27E32F8AD8E2A1C6DDEBB1D235A69E3CEF9BCE90273D" ) ;
 Q = gcry_mpi_point_new ( 0 ) ;
 err = ec_p_new ( & ctx , P , A ) ;
 if ( err ) die ( "ec_p_new failed: %s\n" , gpg_strerror ( err ) ) ;
 x = gcry_mpi_new ( 0 ) ;
 y = gcry_mpi_new ( 0 ) ;
 z = gcry_mpi_new ( 0 ) ;
 {
 gcry_mpi_t tmp ;
 tmp = gcry_mpi_new ( 0 ) ;
 gcry_mpi_ec_mul ( Q , tmp , G , ctx ) ;
 gcry_mpi_release ( tmp ) ;
 gcry_mpi_point_get ( x , y , z , Q ) ;
 if ( gcry_mpi_cmp_ui ( x , 0 ) || gcry_mpi_cmp_ui ( y , 0 ) || gcry_mpi_cmp_ui ( z , 0 ) ) fail ( "multiply a point by zero failed\n" ) ;
 }
 gcry_mpi_ec_mul ( Q , d , G , ctx ) ;
 gcry_mpi_point_get ( x , y , z , Q ) ;
 if ( cmp_mpihex ( x , "222D9EC717C89D047E0898C9185B033CD11C0A981EE6DC66" ) || cmp_mpihex ( y , "605DE0A82D70D3E0F84A127D0739ED33D657DF0D054BFDE8" ) || cmp_mpihex ( z , "00B06B519071BC536999AC8F2D3934B3C1FC9EACCD0A31F88F" ) ) fail ( "computed public key does not match\n" ) ;
 if ( debug ) {
 print_mpi ( "Q.x" , x ) ;
 print_mpi ( "Q.y" , y ) ;
 print_mpi ( "Q.z" , z ) ;
 }
 if ( gcry_mpi_ec_get_affine ( x , y , Q , ctx ) ) fail ( "failed to get affine coordinates\n" ) ;
 if ( cmp_mpihex ( x , "008532093BA023F4D55C0424FA3AF9367E05F309DC34CDC3FE" ) || cmp_mpihex ( y , "00C13CA9E617C6C8487BFF6A726E3C4F277913D97117939966" ) ) fail ( "computed affine coordinates of public key do not match\n" ) ;
 if ( debug ) {
 print_mpi ( "q.x" , x ) ;
 print_mpi ( "q.y" , y ) ;
 }
 gcry_mpi_release ( z ) ;
 gcry_mpi_release ( y ) ;
 gcry_mpi_release ( x ) ;
 gcry_mpi_point_release ( Q ) ;
 gcry_mpi_release ( d ) ;
 gcry_mpi_point_release ( G ) ;
 gcry_mpi_release ( A ) ;
 gcry_mpi_release ( P ) ;
 gcry_ctx_release ( ctx ) ;
 }