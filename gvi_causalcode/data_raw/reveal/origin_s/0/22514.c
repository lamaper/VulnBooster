static void print_time ( const char * label , int64_t etl ) {
 int64_t hours ;
 int64_t mins ;
 int64_t secs ;
 if ( etl >= 0 ) {
 hours = etl / 3600 ;
 etl -= hours * 3600 ;
 mins = etl / 60 ;
 etl -= mins * 60 ;
 secs = etl ;
 fprintf ( stderr , "[%3s %2" PRId64 ":%02" PRId64 ":%02" PRId64 "] " , label , hours , mins , secs ) ;
 }
 else {
 fprintf ( stderr , "[%3s unknown] " , label ) ;
 }
 }