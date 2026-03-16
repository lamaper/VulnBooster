static void subtract_stats ( FIRSTPASS_STATS * section , const FIRSTPASS_STATS * frame ) {
 section -> frame -= frame -> frame ;
 section -> intra_error -= frame -> intra_error ;
 section -> coded_error -= frame -> coded_error ;
 section -> sr_coded_error -= frame -> sr_coded_error ;
 section -> pcnt_inter -= frame -> pcnt_inter ;
 section -> pcnt_motion -= frame -> pcnt_motion ;
 section -> pcnt_second_ref -= frame -> pcnt_second_ref ;
 section -> pcnt_neutral -= frame -> pcnt_neutral ;
 section -> MVr -= frame -> MVr ;
 section -> mvr_abs -= frame -> mvr_abs ;
 section -> MVc -= frame -> MVc ;
 section -> mvc_abs -= frame -> mvc_abs ;
 section -> MVrv -= frame -> MVrv ;
 section -> MVcv -= frame -> MVcv ;
 section -> mv_in_out_count -= frame -> mv_in_out_count ;
 section -> new_mv_count -= frame -> new_mv_count ;
 section -> count -= frame -> count ;
 section -> duration -= frame -> duration ;
 }