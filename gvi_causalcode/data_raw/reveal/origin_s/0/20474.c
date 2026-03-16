static int calculate_boost_bits ( int frame_count , int boost , int64_t total_group_bits ) {
 int allocation_chunks ;
 if ( ! boost || ( total_group_bits <= 0 ) || ( frame_count <= 0 ) ) return 0 ;
 allocation_chunks = ( frame_count * 100 ) + boost ;
 if ( boost > 1023 ) {
 int divisor = boost >> 10 ;
 boost /= divisor ;
 allocation_chunks /= divisor ;
 }
 return MAX ( ( int ) ( ( ( int64_t ) boost * total_group_bits ) / allocation_chunks ) , 0 ) ;
 }