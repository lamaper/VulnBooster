static MV mi_mv_pred_q4 ( const MODE_INFO * mi , int idx ) {
 MV res = {
 round_mv_comp_q4 ( mi -> bmi [ 0 ] . as_mv [ idx ] . as_mv . row + mi -> bmi [ 1 ] . as_mv [ idx ] . as_mv . row + mi -> bmi [ 2 ] . as_mv [ idx ] . as_mv . row + mi -> bmi [ 3 ] . as_mv [ idx ] . as_mv . row ) , round_mv_comp_q4 ( mi -> bmi [ 0 ] . as_mv [ idx ] . as_mv . col + mi -> bmi [ 1 ] . as_mv [ idx ] . as_mv . col + mi -> bmi [ 2 ] . as_mv [ idx ] . as_mv . col + mi -> bmi [ 3 ] . as_mv [ idx ] . as_mv . col ) }
 ;
 return res ;
 }