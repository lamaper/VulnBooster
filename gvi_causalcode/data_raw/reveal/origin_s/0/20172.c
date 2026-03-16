static void lfe_interpolation_fir ( DCAContext * s , int decimation_select , int num_deci_sample , float * samples_in , float * samples_out , float scale ) {
 int decifactor ;
 const float * prCoeff ;
 int deciindex ;
 if ( decimation_select == 1 ) {
 decifactor = 64 ;
 prCoeff = lfe_fir_128 ;
 }
 else {
 decifactor = 32 ;
 prCoeff = lfe_fir_64 ;
 }
 for ( deciindex = 0 ;
 deciindex < num_deci_sample ;
 deciindex ++ ) {
 s -> dcadsp . lfe_fir ( samples_out , samples_in , prCoeff , decifactor , scale ) ;
 samples_in ++ ;
 samples_out += 2 * decifactor ;
 }
 }