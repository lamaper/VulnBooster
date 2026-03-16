static void set_rc_buffer_sizes ( RATE_CONTROL * rc , const VP9EncoderConfig * oxcf ) {
 const int64_t bandwidth = oxcf -> target_bandwidth ;
 const int64_t starting = oxcf -> starting_buffer_level_ms ;
 const int64_t optimal = oxcf -> optimal_buffer_level_ms ;
 const int64_t maximum = oxcf -> maximum_buffer_size_ms ;
 rc -> starting_buffer_level = starting * bandwidth / 1000 ;
 rc -> optimal_buffer_level = ( optimal == 0 ) ? bandwidth / 8 : optimal * bandwidth / 1000 ;
 rc -> maximum_buffer_size = ( maximum == 0 ) ? bandwidth / 8 : maximum * bandwidth / 1000 ;
 }