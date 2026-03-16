void vp9_cyclic_refresh_set_rate_and_dist_sb ( CYCLIC_REFRESH * cr , int64_t rate_sb , int64_t dist_sb ) {
 cr -> projected_rate_sb = rate_sb ;
 cr -> projected_dist_sb = dist_sb ;
 }