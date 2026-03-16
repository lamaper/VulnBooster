bool i_stream_attachment_extractor_can_retry ( struct istream * input ) {
 struct attachment_istream * astream = ( struct attachment_istream * ) input -> real_stream ;
 return astream -> retry_read ;
 }