static int get_ref_frame_flags ( const VP9_COMP * cpi ) {
 const int * const map = cpi -> common . ref_frame_map ;
 const int gold_is_last = map [ cpi -> gld_fb_idx ] == map [ cpi -> lst_fb_idx ] ;
 const int alt_is_last = map [ cpi -> alt_fb_idx ] == map [ cpi -> lst_fb_idx ] ;
 const int gold_is_alt = map [ cpi -> gld_fb_idx ] == map [ cpi -> alt_fb_idx ] ;
 int flags = VP9_ALT_FLAG | VP9_GOLD_FLAG | VP9_LAST_FLAG ;
 if ( gold_is_last ) flags &= ~ VP9_GOLD_FLAG ;
 if ( cpi -> rc . frames_till_gf_update_due == INT_MAX && ! is_two_pass_svc ( cpi ) ) flags &= ~ VP9_GOLD_FLAG ;
 if ( alt_is_last ) flags &= ~ VP9_ALT_FLAG ;
 if ( gold_is_alt ) flags &= ~ VP9_ALT_FLAG ;
 return flags ;
 }