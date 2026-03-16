static int asf_write_trailer ( AVFormatContext * s ) {
 ASFContext * asf = s -> priv_data ;
 int64_t file_size , data_size ;
 int ret ;
 if ( asf -> pb . buf_ptr > asf -> pb . buffer ) flush_packet ( s ) ;
 data_size = avio_tell ( s -> pb ) ;
 if ( ! asf -> is_streamed && asf -> next_start_sec ) {
 if ( ( ret = update_index ( s , asf -> end_sec + 1 , 0 , 0 , 0 ) ) < 0 ) return ret ;
 asf_write_index ( s , asf -> index_ptr , asf -> maximum_packet , asf -> next_start_sec ) ;
 }
 avio_flush ( s -> pb ) ;
 if ( asf -> is_streamed || ! s -> pb -> seekable ) {
 put_chunk ( s , 0x4524 , 0 , 0 ) ;
 }
 else {
 file_size = avio_tell ( s -> pb ) ;
 avio_seek ( s -> pb , 0 , SEEK_SET ) ;
 asf_write_header1 ( s , file_size , data_size - asf -> data_offset ) ;
 }
 av_freep ( & asf -> index_ptr ) ;
 return 0 ;
 }