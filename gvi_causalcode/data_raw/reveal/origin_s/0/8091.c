static int update_index ( AVFormatContext * s , int start_sec , uint32_t packet_number , uint16_t packet_count , uint64_t packet_offset ) {
 ASFContext * asf = s -> priv_data ;
 if ( start_sec > asf -> next_start_sec ) {
 int i ;
 if ( ! asf -> next_start_sec ) {
 asf -> next_packet_number = packet_number ;
 asf -> next_packet_count = packet_count ;
 asf -> next_packet_offset = packet_offset ;
 }
 if ( start_sec > asf -> nb_index_memory_alloc ) {
 int err ;
 asf -> nb_index_memory_alloc = ( start_sec + ASF_INDEX_BLOCK ) & ~ ( ASF_INDEX_BLOCK - 1 ) ;
 if ( ( err = av_reallocp_array ( & asf -> index_ptr , asf -> nb_index_memory_alloc , sizeof ( * asf -> index_ptr ) ) ) < 0 ) {
 asf -> nb_index_memory_alloc = 0 ;
 return err ;
 }
 }
 for ( i = asf -> next_start_sec ;
 i < start_sec ;
 i ++ ) {
 asf -> index_ptr [ i ] . packet_number = asf -> next_packet_number ;
 asf -> index_ptr [ i ] . packet_count = asf -> next_packet_count ;
 asf -> index_ptr [ i ] . send_time = asf -> next_start_sec * INT64_C ( 10000000 ) ;
 asf -> index_ptr [ i ] . offset = asf -> next_packet_offset ;
 }
 }
 asf -> maximum_packet = FFMAX ( asf -> maximum_packet , packet_count ) ;
 asf -> next_packet_number = packet_number ;
 asf -> next_packet_count = packet_count ;
 asf -> next_packet_offset = packet_offset ;
 asf -> next_start_sec = start_sec ;
 return 0 ;
 }