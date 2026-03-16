static ssize_t i_stream_attachment_extractor_read ( struct istream_private * stream ) {
 struct attachment_istream * astream = ( struct attachment_istream * ) stream ;
 bool retry ;
 ssize_t ret ;
 do {
 ret = astream_read_next ( astream , & retry ) ;
 }
 while ( retry && astream -> set . drain_parent_input ) ;
 astream -> retry_read = retry ;
 return ret ;
 }