static int sse_diff_thresh ( BLOCK_SIZE bs , int increase_denoising , int mv_row , int mv_col ) {
 if ( mv_row * mv_row + mv_col * mv_col > noise_motion_thresh ( bs , increase_denoising ) ) {
 return 0 ;
 }
 else {
 return widths [ bs ] * heights [ bs ] * 20 ;
 }
 }