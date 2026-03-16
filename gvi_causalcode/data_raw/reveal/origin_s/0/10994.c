static int raw_read_frame ( FILE * infile , uint8_t * * buffer , size_t * bytes_read , size_t * buffer_size ) {
 char raw_hdr [ RAW_FRAME_HDR_SZ ] ;
 size_t frame_size = 0 ;
 if ( fread ( raw_hdr , RAW_FRAME_HDR_SZ , 1 , infile ) != 1 ) {
 if ( ! feof ( infile ) ) warn ( "Failed to read RAW frame size\n" ) ;
 }
 else {
 const size_t kCorruptFrameThreshold = 256 * 1024 * 1024 ;
 const size_t kFrameTooSmallThreshold = 256 * 1024 ;
 frame_size = mem_get_le32 ( raw_hdr ) ;
 if ( frame_size > kCorruptFrameThreshold ) {
 warn ( "Read invalid frame size (%u)\n" , ( unsigned int ) frame_size ) ;
 frame_size = 0 ;
 }
 if ( frame_size < kFrameTooSmallThreshold ) {
 warn ( "Warning: Read invalid frame size (%u) - not a raw file?\n" , ( unsigned int ) frame_size ) ;
 }
 if ( frame_size > * buffer_size ) {
 uint8_t * new_buf = realloc ( * buffer , 2 * frame_size ) ;
 if ( new_buf ) {
 * buffer = new_buf ;
 * buffer_size = 2 * frame_size ;
 }
 else {
 warn ( "Failed to allocate compressed data buffer\n" ) ;
 frame_size = 0 ;
 }
 }
 }
 if ( ! feof ( infile ) ) {
 if ( fread ( * buffer , 1 , frame_size , infile ) != frame_size ) {
 warn ( "Failed to read full frame\n" ) ;
 return 1 ;
 }
 * bytes_read = frame_size ;
 }
 return 0 ;
 }