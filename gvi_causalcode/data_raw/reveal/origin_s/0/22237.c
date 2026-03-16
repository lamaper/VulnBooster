static double calculate_modified_err ( const TWO_PASS * twopass , const VP9EncoderConfig * oxcf , const FIRSTPASS_STATS * this_frame ) {
 const FIRSTPASS_STATS * const stats = & twopass -> total_stats ;
 const double av_err = stats -> coded_error / stats -> count ;
 const double modified_error = av_err * pow ( this_frame -> coded_error / DOUBLE_DIVIDE_CHECK ( av_err ) , oxcf -> two_pass_vbrbias / 100.0 ) ;
 return fclamp ( modified_error , twopass -> modified_error_min , twopass -> modified_error_max ) ;
 }