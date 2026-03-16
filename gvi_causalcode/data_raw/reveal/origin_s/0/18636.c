double vp8_gaussian ( double sigma , double mu , double x ) {
 return 1 / ( sigma * sqrt ( 2.0 * 3.14159265 ) ) * ( exp ( - ( x - mu ) * ( x - mu ) / ( 2 * sigma * sigma ) ) ) ;
 }