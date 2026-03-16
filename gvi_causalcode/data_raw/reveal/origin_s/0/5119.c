static MV average_split_mvs ( const struct macroblockd_plane * pd , const MODE_INFO * mi , int ref , int block ) {
 const int ss_idx = ( ( pd -> subsampling_x > 0 ) << 1 ) | ( pd -> subsampling_y > 0 ) ;
 MV res = {
 0 , 0 }
 ;
 switch ( ss_idx ) {
 case 0 : res = mi -> bmi [ block ] . as_mv [ ref ] . as_mv ;
 break ;
 case 1 : res = mi_mv_pred_q2 ( mi , ref , block , block + 2 ) ;
 break ;
 case 2 : res = mi_mv_pred_q2 ( mi , ref , block , block + 1 ) ;
 break ;
 case 3 : res = mi_mv_pred_q4 ( mi , ref ) ;
 break ;
 default : assert ( ss_idx <= 3 || ss_idx >= 0 ) ;
 }
 return res ;
 }