static void twistededwards_math ( void ) {
 gpg_error_t err ;
 gcry_ctx_t ctx ;
 gcry_mpi_point_t G , Q ;
 gcry_mpi_t k ;
 gcry_mpi_t w , a , x , y , z , p , n , b , I ;
 wherestr = "twistededwards_math" ;
 show ( "checking basic Twisted Edwards math\n" ) ;
 err = gcry_mpi_ec_new ( & ctx , NULL , "Ed25519" ) ;
 if ( err ) die ( "gcry_mpi_ec_new failed: %s\n" , gpg_strerror ( err ) ) ;
 k = hex2mpi ( "2D3501E723239632802454EE5DDC406EFB0BDF18486A5BDE9C0390A9C2984004" "F47252B628C953625B8DEB5DBCB8DA97AA43A1892D11FA83596F42E0D89CB1B6" ) ;
 G = gcry_mpi_ec_get_point ( "g" , ctx , 1 ) ;
 if ( ! G ) die ( "gcry_mpi_ec_get_point(G) failed\n" ) ;
 Q = gcry_mpi_point_new ( 0 ) ;
 w = gcry_mpi_new ( 0 ) ;
 a = gcry_mpi_new ( 0 ) ;
 x = gcry_mpi_new ( 0 ) ;
 y = gcry_mpi_new ( 0 ) ;
 z = gcry_mpi_new ( 0 ) ;
 I = gcry_mpi_new ( 0 ) ;
 p = gcry_mpi_ec_get_mpi ( "p" , ctx , 1 ) ;
 n = gcry_mpi_ec_get_mpi ( "n" , ctx , 1 ) ;
 b = gcry_mpi_ec_get_mpi ( "b" , ctx , 1 ) ;
 gcry_mpi_sub_ui ( a , p , 1 ) ;
 gcry_mpi_powm ( w , GCRYMPI_CONST_TWO , a , p ) ;
 if ( gcry_mpi_cmp_ui ( w , 1 ) ) fail ( "failed assertion: 2^{
p-1}
 mod p == 1\n" ) ;
 gcry_mpi_mod ( w , p , GCRYMPI_CONST_FOUR ) ;
 if ( gcry_mpi_cmp_ui ( w , 1 ) ) fail ( "failed assertion: p % 4 == 1\n" ) ;
 gcry_mpi_sub_ui ( a , n , 1 ) ;
 gcry_mpi_powm ( w , GCRYMPI_CONST_TWO , a , n ) ;
 if ( gcry_mpi_cmp_ui ( w , 1 ) ) fail ( "failed assertion: 2^{
n-1}
 mod n == 1\n" ) ;
 gcry_mpi_sub_ui ( a , p , 1 ) ;
 gcry_mpi_div ( x , NULL , a , GCRYMPI_CONST_TWO , - 1 ) ;
 gcry_mpi_powm ( w , b , x , p ) ;
 gcry_mpi_abs ( w ) ;
 if ( gcry_mpi_cmp ( w , a ) ) fail ( "failed assertion: b^{
(p-1)/2}
 mod p == p-1\n" ) ;
 gcry_mpi_sub_ui ( a , p , 1 ) ;
 gcry_mpi_div ( x , NULL , a , GCRYMPI_CONST_FOUR , - 1 ) ;
 gcry_mpi_powm ( I , GCRYMPI_CONST_TWO , x , p ) ;
 gcry_mpi_powm ( w , I , GCRYMPI_CONST_TWO , p ) ;
 if ( gcry_mpi_cmp ( w , a ) ) fail ( "failed assertion: I^2 mod p == p-1\n" ) ;
 if ( ! gcry_mpi_ec_curve_point ( G , ctx ) ) fail ( "failed assertion: G is on the curve\n" ) ;
 gcry_mpi_ec_mul ( Q , n , G , ctx ) ;
 if ( gcry_mpi_ec_get_affine ( x , y , Q , ctx ) ) fail ( "failed to get affine coordinates\n" ) ;
 if ( gcry_mpi_cmp_ui ( x , 0 ) || gcry_mpi_cmp_ui ( y , 1 ) ) fail ( "failed assertion: nG == (0,1)\n" ) ;
 gcry_mpi_release ( a ) ;
 a = hex2mpi ( "4f71d012df3c371af3ea4dc38385ca5bb7272f90cb1b008b3ed601c76de1d496" "e30cbf625f0a756a678d8f256d5325595cccc83466f36db18f0178eb9925edd3" ) ;
 gcry_mpi_ec_mul ( Q , a , G , ctx ) ;
 if ( gcry_mpi_ec_get_affine ( x , y , Q , ctx ) ) fail ( "failed to get affine coordinates\n" ) ;
 if ( cmp_mpihex ( x , ( "157f7361c577aad36f67ed33e38dc7be" "00014fecc2165ca5cee9eee19fe4d2c1" ) ) || cmp_mpihex ( y , ( "5a69dbeb232276b38f3f5016547bb2a2" "4025645f0b820e72b8cad4f0a909a092" ) ) ) {
 fail ( "sample point multiply failed:\n" ) ;
 print_mpi ( "r" , a ) ;
 print_mpi ( "Rx" , x ) ;
 print_mpi ( "Ry" , y ) ;
 }
 gcry_mpi_release ( a ) ;
 a = hex2mpi ( "2d3501e723239632802454ee5ddc406efb0bdf18486a5bde9c0390a9c2984004" "f47252b628c953625b8deb5dbcb8da97aa43a1892d11fa83596f42e0d89cb1b6" ) ;
 gcry_mpi_ec_mul ( Q , a , G , ctx ) ;
 if ( gcry_mpi_ec_get_affine ( x , y , Q , ctx ) ) fail ( "failed to get affine coordinates\n" ) ;
 if ( cmp_mpihex ( x , ( "6218e309d40065fcc338b3127f468371" "82324bd01ce6f3cf81ab44e62959c82a" ) ) || cmp_mpihex ( y , ( "5501492265e073d874d9e5b81e7f8784" "8a826e80cce2869072ac60c3004356e5" ) ) ) {
 fail ( "sample point multiply failed:\n" ) ;
 print_mpi ( "r" , a ) ;
 print_mpi ( "Rx" , x ) ;
 print_mpi ( "Ry" , y ) ;
 }
 gcry_mpi_release ( I ) ;
 gcry_mpi_release ( b ) ;
 gcry_mpi_release ( n ) ;
 gcry_mpi_release ( p ) ;
 gcry_mpi_release ( w ) ;
 gcry_mpi_release ( a ) ;
 gcry_mpi_release ( x ) ;
 gcry_mpi_release ( y ) ;
 gcry_mpi_release ( z ) ;
 gcry_mpi_point_release ( Q ) ;
 gcry_mpi_point_release ( G ) ;
 gcry_mpi_release ( k ) ;
 gcry_ctx_release ( ctx ) ;
 }