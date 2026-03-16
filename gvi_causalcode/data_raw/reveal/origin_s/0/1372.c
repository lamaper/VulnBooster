ink_time_t ink_cluster_time ( ) {
 int highest_delta ;
 ink_time_t local_time ;
 local_time = Thread : : get_hrtime ( ) / HRTIME_SECOND ;
 highest_delta = ( int ) HttpConfig : : m_master . cluster_time_delta ;
 Debug ( "http_trans" , "[ink_cluster_time] local: %" PRId64 ", highest_delta: %d, cluster: %" PRId64 , ( int64_t ) local_time , highest_delta , ( int64_t ) ( local_time + ( ink_time_t ) highest_delta ) ) ;
 ink_assert ( highest_delta >= 0 ) ;
 return local_time + ( ink_time_t ) highest_delta ;
 }