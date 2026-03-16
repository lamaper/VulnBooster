void open_input_file ( struct VpxInputContext * input ) {
 input -> file = strcmp ( input -> filename , "-" ) ? fopen ( input -> filename , "rb" ) : set_binary_mode ( stdin ) ;
 if ( ! input -> file ) fatal ( "Failed to open input file" ) ;
 if ( ! fseeko ( input -> file , 0 , SEEK_END ) ) {
 input -> length = ftello ( input -> file ) ;
 rewind ( input -> file ) ;
 }
 input -> detect . buf_read = fread ( input -> detect . buf , 1 , 4 , input -> file ) ;
 input -> detect . position = 0 ;
 if ( input -> detect . buf_read == 4 && file_is_y4m ( input -> detect . buf ) ) {
 if ( y4m_input_open ( & input -> y4m , input -> file , input -> detect . buf , 4 , input -> only_i420 ) >= 0 ) {
 input -> file_type = FILE_TYPE_Y4M ;
 input -> width = input -> y4m . pic_w ;
 input -> height = input -> y4m . pic_h ;
 input -> framerate . numerator = input -> y4m . fps_n ;
 input -> framerate . denominator = input -> y4m . fps_d ;
 input -> fmt = input -> y4m . vpx_fmt ;
 input -> bit_depth = input -> y4m . bit_depth ;
 }
 else fatal ( "Unsupported Y4M stream." ) ;
 }
 else if ( input -> detect . buf_read == 4 && fourcc_is_ivf ( input -> detect . buf ) ) {
 fatal ( "IVF is not supported as input." ) ;
 }
 else {
 input -> file_type = FILE_TYPE_RAW ;
 }
 }