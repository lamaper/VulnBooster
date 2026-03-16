static int test_candidate_kf ( TWO_PASS * twopass , const FIRSTPASS_STATS * last_frame , const FIRSTPASS_STATS * this_frame , const FIRSTPASS_STATS * next_frame ) {
 int is_viable_kf = 0 ;
 if ( ( this_frame -> pcnt_second_ref < 0.10 ) && ( next_frame -> pcnt_second_ref < 0.10 ) && ( ( this_frame -> pcnt_inter < 0.05 ) || ( ( ( this_frame -> pcnt_inter - this_frame -> pcnt_neutral ) < 0.35 ) && ( ( this_frame -> intra_error / DOUBLE_DIVIDE_CHECK ( this_frame -> coded_error ) ) < 2.5 ) && ( ( fabs ( last_frame -> coded_error - this_frame -> coded_error ) / DOUBLE_DIVIDE_CHECK ( this_frame -> coded_error ) > 0.40 ) || ( fabs ( last_frame -> intra_error - this_frame -> intra_error ) / DOUBLE_DIVIDE_CHECK ( this_frame -> intra_error ) > 0.40 ) || ( ( next_frame -> intra_error / DOUBLE_DIVIDE_CHECK ( next_frame -> coded_error ) ) > 3.5 ) ) ) ) ) {
 int i ;
 const FIRSTPASS_STATS * start_pos = twopass -> stats_in ;
 FIRSTPASS_STATS local_next_frame = * next_frame ;
 double boost_score = 0.0 ;
 double old_boost_score = 0.0 ;
 double decay_accumulator = 1.0 ;
 for ( i = 0 ;
 i < 16 ;
 ++ i ) {
 double next_iiratio = ( BOOST_FACTOR * local_next_frame . intra_error / DOUBLE_DIVIDE_CHECK ( local_next_frame . coded_error ) ) ;
 if ( next_iiratio > KF_II_MAX ) next_iiratio = KF_II_MAX ;
 if ( local_next_frame . pcnt_inter > 0.85 ) decay_accumulator *= local_next_frame . pcnt_inter ;
 else decay_accumulator *= ( 0.85 + local_next_frame . pcnt_inter ) / 2.0 ;
 boost_score += ( decay_accumulator * next_iiratio ) ;
 if ( ( local_next_frame . pcnt_inter < 0.05 ) || ( next_iiratio < 1.5 ) || ( ( ( local_next_frame . pcnt_inter - local_next_frame . pcnt_neutral ) < 0.20 ) && ( next_iiratio < 3.0 ) ) || ( ( boost_score - old_boost_score ) < 3.0 ) || ( local_next_frame . intra_error < 200 ) ) {
 break ;
 }
 old_boost_score = boost_score ;
 if ( EOF == input_stats ( twopass , & local_next_frame ) ) break ;
 }
 if ( boost_score > 30.0 && ( i > 3 ) ) {
 is_viable_kf = 1 ;
 }
 else {
 reset_fpf_position ( twopass , start_pos ) ;
 is_viable_kf = 0 ;
 }
 }
 return is_viable_kf ;
 }