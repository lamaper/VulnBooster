static inline double freq2bark ( double freq ) {
 return 3.5 * atan ( ( freq / 7500.0 ) * ( freq / 7500.0 ) ) + 13.0 * atan ( freq * 0.00076 ) ;
 }