void sum_2_variances ( const var * a , const var * b , var * r ) {
 fill_variance ( a -> sum_square_error + b -> sum_square_error , a -> sum_error + b -> sum_error , a -> count + b -> count , r ) ;
 }