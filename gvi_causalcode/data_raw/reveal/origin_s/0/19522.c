static int asf_write_stream_header ( AVFormatContext * s ) {
 ASFContext * asf = s -> priv_data ;
 asf -> is_streamed = 1 ;
 return asf_write_header ( s ) ;
 }