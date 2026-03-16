static void flush_packet ( AVFormatContext * s ) {
 ASFContext * asf = s -> priv_data ;
 int packet_hdr_size , packet_filled_size ;
 av_assert0 ( asf -> packet_timestamp_end >= asf -> packet_timestamp_start ) ;
 if ( asf -> is_streamed ) put_chunk ( s , 0x4424 , s -> packet_size , 0 ) ;
 packet_hdr_size = put_payload_parsing_info ( s , asf -> packet_timestamp_start , asf -> packet_timestamp_end - asf -> packet_timestamp_start , asf -> packet_nb_payloads , asf -> packet_size_left ) ;
 packet_filled_size = PACKET_SIZE - asf -> packet_size_left ;
 av_assert0 ( packet_hdr_size <= asf -> packet_size_left ) ;
 memset ( asf -> packet_buf + packet_filled_size , 0 , asf -> packet_size_left ) ;
 avio_write ( s -> pb , asf -> packet_buf , s -> packet_size - packet_hdr_size ) ;
 avio_flush ( s -> pb ) ;
 asf -> nb_packets ++ ;
 asf -> packet_nb_payloads = 0 ;
 asf -> packet_timestamp_start = - 1 ;
 asf -> packet_timestamp_end = - 1 ;
 ffio_init_context ( & asf -> pb , asf -> packet_buf , s -> packet_size , 1 , NULL , NULL , NULL , NULL ) ;
 }