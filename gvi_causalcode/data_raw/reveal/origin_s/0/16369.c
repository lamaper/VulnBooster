static PyObject * datetime_from_millis ( long long millis ) {
 int diff = ( int ) ( ( ( millis % 1000 ) + 1000 ) % 1000 ) ;
 int microseconds = diff * 1000 ;
 Time64_T seconds = ( millis - diff ) / 1000 ;
 struct TM timeinfo ;
 gmtime64_r ( & seconds , & timeinfo ) ;
 return PyDateTime_FromDateAndTime ( timeinfo . tm_year + 1900 , timeinfo . tm_mon + 1 , timeinfo . tm_mday , timeinfo . tm_hour , timeinfo . tm_min , timeinfo . tm_sec , microseconds ) ;
 }