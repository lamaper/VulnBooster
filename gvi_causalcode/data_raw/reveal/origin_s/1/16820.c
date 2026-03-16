static double calc_correction_factor ( double err_per_mb , double err_divisor , double pt_low , double pt_high , int q ) {
 const double error_term = err_per_mb / err_divisor ;
 const double power_term = MIN ( vp9_convert_qindex_to_q ( q ) * 0.0125 + pt_low , pt_high ) ;
 if ( power_term < 1.0 ) assert ( error_term >= 0.0 ) ;
 return fclamp ( pow ( error_term , power_term ) , 0.05 , 5.0 ) ;
 }