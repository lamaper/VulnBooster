static time_t my_timegm ( struct my_tm * tm ) {
 static const int month_days_cumulative [ 12 ] = {
 0 , 31 , 59 , 90 , 120 , 151 , 181 , 212 , 243 , 273 , 304 , 334 }
 ;
 int month , year , leap_days ;
 if ( tm -> tm_year < 70 ) return - 1 ;
 year = tm -> tm_year + 1900 ;
 month = tm -> tm_mon ;
 if ( month < 0 ) {
 year += ( 11 - month ) / 12 ;
 month = 11 - ( 11 - month ) % 12 ;
 }
 else if ( month >= 12 ) {
 year -= month / 12 ;
 month = month % 12 ;
 }
 leap_days = year - ( tm -> tm_mon <= 1 ) ;
 leap_days = ( ( leap_days / 4 ) - ( leap_days / 100 ) + ( leap_days / 400 ) - ( 1969 / 4 ) + ( 1969 / 100 ) - ( 1969 / 400 ) ) ;
 return ( ( ( ( time_t ) ( year - 1970 ) * 365 + leap_days + month_days_cumulative [ month ] + tm -> tm_mday - 1 ) * 24 + tm -> tm_hour ) * 60 + tm -> tm_min ) * 60 + tm -> tm_sec ;
 }