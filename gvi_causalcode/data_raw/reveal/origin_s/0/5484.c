double expression_returns_set_rows ( Node * clause ) {
 double result = 1 ;
 ( void ) expression_returns_set_rows_walker ( clause , & result ) ;
 return clamp_row_est ( result ) ;
 }