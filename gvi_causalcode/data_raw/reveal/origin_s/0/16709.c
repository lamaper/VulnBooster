static MV mi_mv_pred_q2 ( const MODE_INFO * mi , int idx , int block0 , int block1 ) {
 MV res = {
 round_mv_comp_q2 ( mi -> bmi [ block0 ] . as_mv [ idx ] . as_mv . row + mi -> bmi [ block1 ] . as_mv [ idx ] . as_mv . row ) , round_mv_comp_q2 ( mi -> bmi [ block0 ] . as_mv [ idx ] . as_mv . col + mi -> bmi [ block1 ] . as_mv [ idx ] . as_mv . col ) }
 ;
 return res ;
 }