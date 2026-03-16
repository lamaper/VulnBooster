static void get_tmfromtime ( struct tm * tm , time_t * t ) {

 localtime_r ( t , tm ) ;


