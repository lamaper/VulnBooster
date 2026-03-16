int y4m_input_open ( y4m_input * _y4m , FILE * _fin , char * _skip , int _nskip , int only_420 ) {
 char buffer [ 80 ] = {
 0 }
 ;
 int ret ;
 int i ;
 for ( i = 0 ;
 i < 79 ;
 i ++ ) {
 if ( _nskip > 0 ) {
 buffer [ i ] = * _skip ++ ;
 _nskip -- ;
 }
 else {
 if ( ! file_read ( buffer + i , 1 , _fin ) ) return - 1 ;
 }
 if ( buffer [ i ] == '\n' ) break ;
 }
 if ( _nskip > 0 ) return - 1 ;
 if ( i == 79 ) {
 fprintf ( stderr , "Error parsing header;
 not a YUV2MPEG2 file?\n" ) ;
 return - 1 ;
 }
 buffer [ i ] = '\0' ;
 if ( memcmp ( buffer , "YUV4MPEG" , 8 ) ) {
 fprintf ( stderr , "Incomplete magic for YUV4MPEG file.\n" ) ;
 return - 1 ;
 }
 if ( buffer [ 8 ] != '2' ) {
 fprintf ( stderr , "Incorrect YUV input file version;
 YUV4MPEG2 required.\n" ) ;
 }
 ret = y4m_parse_tags ( _y4m , buffer + 5 ) ;
 if ( ret < 0 ) {
 fprintf ( stderr , "Error parsing YUV4MPEG2 header.\n" ) ;
 return ret ;
 }
 if ( _y4m -> interlace == '?' ) {
 fprintf ( stderr , "Warning: Input video interlacing format unknown;
 " "assuming progressive scan.\n" ) ;
 }
 else if ( _y4m -> interlace != 'p' ) {
 fprintf ( stderr , "Input video is interlaced;
 " "Only progressive scan handled.\n" ) ;
 return - 1 ;
 }
 _y4m -> vpx_fmt = VPX_IMG_FMT_I420 ;
 _y4m -> bps = 12 ;
 _y4m -> bit_depth = 8 ;
 if ( strcmp ( _y4m -> chroma_type , "420" ) == 0 || strcmp ( _y4m -> chroma_type , "420jpeg" ) == 0 ) {
 _y4m -> src_c_dec_h = _y4m -> dst_c_dec_h = _y4m -> src_c_dec_v = _y4m -> dst_c_dec_v = 2 ;
 _y4m -> dst_buf_read_sz = _y4m -> pic_w * _y4m -> pic_h + 2 * ( ( _y4m -> pic_w + 1 ) / 2 ) * ( ( _y4m -> pic_h + 1 ) / 2 ) ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 0 ;
 _y4m -> convert = y4m_convert_null ;
 }
 else if ( strcmp ( _y4m -> chroma_type , "420p10" ) == 0 ) {
 _y4m -> src_c_dec_h = 2 ;
 _y4m -> dst_c_dec_h = 2 ;
 _y4m -> src_c_dec_v = 2 ;
 _y4m -> dst_c_dec_v = 2 ;
 _y4m -> dst_buf_read_sz = 2 * ( _y4m -> pic_w * _y4m -> pic_h + * ( ( _y4m -> pic_w + 1 ) / 2 ) * ( ( _y4m -> pic_h + 1 ) / 2 ) ) ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 0 ;
 _y4m -> convert = y4m_convert_null ;
 _y4m -> bit_depth = 10 ;
 _y4m -> bps = 15 ;
 _y4m -> vpx_fmt = VPX_IMG_FMT_I42016 ;
 if ( only_420 ) {
 fprintf ( stderr , "Unsupported conversion from 420p10 to 420jpeg\n" ) ;
 return - 1 ;
 }
 }
 else if ( strcmp ( _y4m -> chroma_type , "420p12" ) == 0 ) {
 _y4m -> src_c_dec_h = 2 ;
 _y4m -> dst_c_dec_h = 2 ;
 _y4m -> src_c_dec_v = 2 ;
 _y4m -> dst_c_dec_v = 2 ;
 _y4m -> dst_buf_read_sz = 2 * ( _y4m -> pic_w * _y4m -> pic_h + * ( ( _y4m -> pic_w + 1 ) / 2 ) * ( ( _y4m -> pic_h + 1 ) / 2 ) ) ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 0 ;
 _y4m -> convert = y4m_convert_null ;
 _y4m -> bit_depth = 12 ;
 _y4m -> bps = 18 ;
 _y4m -> vpx_fmt = VPX_IMG_FMT_I42016 ;
 if ( only_420 ) {
 fprintf ( stderr , "Unsupported conversion from 420p12 to 420jpeg\n" ) ;
 return - 1 ;
 }
 }
 else if ( strcmp ( _y4m -> chroma_type , "420mpeg2" ) == 0 ) {
 _y4m -> src_c_dec_h = _y4m -> dst_c_dec_h = _y4m -> src_c_dec_v = _y4m -> dst_c_dec_v = 2 ;
 _y4m -> dst_buf_read_sz = _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = * ( ( _y4m -> pic_w + 1 ) / 2 ) * ( ( _y4m -> pic_h + 1 ) / 2 ) ;
 _y4m -> convert = y4m_convert_42xmpeg2_42xjpeg ;
 }
 else if ( strcmp ( _y4m -> chroma_type , "420paldv" ) == 0 ) {
 _y4m -> src_c_dec_h = _y4m -> dst_c_dec_h = _y4m -> src_c_dec_v = _y4m -> dst_c_dec_v = 2 ;
 _y4m -> dst_buf_read_sz = _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = 3 * ( ( _y4m -> pic_w + 1 ) / 2 ) * ( ( _y4m -> pic_h + 1 ) / 2 ) ;
 _y4m -> aux_buf_read_sz = 2 * ( ( _y4m -> pic_w + 1 ) / 2 ) * ( ( _y4m -> pic_h + 1 ) / 2 ) ;
 _y4m -> convert = y4m_convert_42xpaldv_42xjpeg ;
 }
 else if ( strcmp ( _y4m -> chroma_type , "422jpeg" ) == 0 ) {
 _y4m -> src_c_dec_h = _y4m -> dst_c_dec_h = 2 ;
 _y4m -> src_c_dec_v = 1 ;
 _y4m -> dst_c_dec_v = 2 ;
 _y4m -> dst_buf_read_sz = _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 2 * ( ( _y4m -> pic_w + 1 ) / 2 ) * _y4m -> pic_h ;
 _y4m -> convert = y4m_convert_422jpeg_420jpeg ;
 }
 else if ( strcmp ( _y4m -> chroma_type , "422" ) == 0 ) {
 _y4m -> src_c_dec_h = 2 ;
 _y4m -> src_c_dec_v = 1 ;
 if ( only_420 ) {
 _y4m -> dst_c_dec_h = 2 ;
 _y4m -> dst_c_dec_v = 2 ;
 _y4m -> dst_buf_read_sz = _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_read_sz = 2 * ( ( _y4m -> pic_w + 1 ) / 2 ) * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz + ( ( _y4m -> pic_w + 1 ) / 2 ) * _y4m -> pic_h ;
 _y4m -> convert = y4m_convert_422_420jpeg ;
 }
 else {
 _y4m -> vpx_fmt = VPX_IMG_FMT_I422 ;
 _y4m -> bps = 16 ;
 _y4m -> dst_c_dec_h = _y4m -> src_c_dec_h ;
 _y4m -> dst_c_dec_v = _y4m -> src_c_dec_v ;
 _y4m -> dst_buf_read_sz = _y4m -> pic_w * _y4m -> pic_h + 2 * ( ( _y4m -> pic_w + 1 ) / 2 ) * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 0 ;
 _y4m -> convert = y4m_convert_null ;
 }
 }
 else if ( strcmp ( _y4m -> chroma_type , "422p10" ) == 0 ) {
 _y4m -> src_c_dec_h = 2 ;
 _y4m -> src_c_dec_v = 1 ;
 _y4m -> vpx_fmt = VPX_IMG_FMT_I42216 ;
 _y4m -> bps = 20 ;
 _y4m -> bit_depth = 10 ;
 _y4m -> dst_c_dec_h = _y4m -> src_c_dec_h ;
 _y4m -> dst_c_dec_v = _y4m -> src_c_dec_v ;
 _y4m -> dst_buf_read_sz = 2 * ( _y4m -> pic_w * _y4m -> pic_h + * ( ( _y4m -> pic_w + 1 ) / 2 ) * _y4m -> pic_h ) ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 0 ;
 _y4m -> convert = y4m_convert_null ;
 if ( only_420 ) {
 fprintf ( stderr , "Unsupported conversion from 422p10 to 420jpeg\n" ) ;
 return - 1 ;
 }
 }
 else if ( strcmp ( _y4m -> chroma_type , "422p12" ) == 0 ) {
 _y4m -> src_c_dec_h = 2 ;
 _y4m -> src_c_dec_v = 1 ;
 _y4m -> vpx_fmt = VPX_IMG_FMT_I42216 ;
 _y4m -> bps = 24 ;
 _y4m -> bit_depth = 12 ;
 _y4m -> dst_c_dec_h = _y4m -> src_c_dec_h ;
 _y4m -> dst_c_dec_v = _y4m -> src_c_dec_v ;
 _y4m -> dst_buf_read_sz = 2 * ( _y4m -> pic_w * _y4m -> pic_h + * ( ( _y4m -> pic_w + 1 ) / 2 ) * _y4m -> pic_h ) ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 0 ;
 _y4m -> convert = y4m_convert_null ;
 if ( only_420 ) {
 fprintf ( stderr , "Unsupported conversion from 422p12 to 420jpeg\n" ) ;
 return - 1 ;
 }
 }
 else if ( strcmp ( _y4m -> chroma_type , "411" ) == 0 ) {
 _y4m -> src_c_dec_h = 4 ;
 _y4m -> dst_c_dec_h = 2 ;
 _y4m -> src_c_dec_v = 1 ;
 _y4m -> dst_c_dec_v = 2 ;
 _y4m -> dst_buf_read_sz = _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_read_sz = 2 * ( ( _y4m -> pic_w + 3 ) / 4 ) * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz + ( ( _y4m -> pic_w + 1 ) / 2 ) * _y4m -> pic_h ;
 _y4m -> convert = y4m_convert_411_420jpeg ;
 }
 else if ( strcmp ( _y4m -> chroma_type , "444" ) == 0 ) {
 _y4m -> src_c_dec_h = 1 ;
 _y4m -> src_c_dec_v = 1 ;
 if ( only_420 ) {
 _y4m -> dst_c_dec_h = 2 ;
 _y4m -> dst_c_dec_v = 2 ;
 _y4m -> dst_buf_read_sz = _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_read_sz = 2 * _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz + ( ( _y4m -> pic_w + 1 ) / 2 ) * _y4m -> pic_h ;
 _y4m -> convert = y4m_convert_444_420jpeg ;
 }
 else {
 _y4m -> vpx_fmt = VPX_IMG_FMT_I444 ;
 _y4m -> bps = 24 ;
 _y4m -> dst_c_dec_h = _y4m -> src_c_dec_h ;
 _y4m -> dst_c_dec_v = _y4m -> src_c_dec_v ;
 _y4m -> dst_buf_read_sz = 3 * _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 0 ;
 _y4m -> convert = y4m_convert_null ;
 }
 }
 else if ( strcmp ( _y4m -> chroma_type , "444p10" ) == 0 ) {
 _y4m -> src_c_dec_h = 1 ;
 _y4m -> src_c_dec_v = 1 ;
 _y4m -> vpx_fmt = VPX_IMG_FMT_I44416 ;
 _y4m -> bps = 30 ;
 _y4m -> bit_depth = 10 ;
 _y4m -> dst_c_dec_h = _y4m -> src_c_dec_h ;
 _y4m -> dst_c_dec_v = _y4m -> src_c_dec_v ;
 _y4m -> dst_buf_read_sz = 2 * 3 * _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 0 ;
 _y4m -> convert = y4m_convert_null ;
 if ( only_420 ) {
 fprintf ( stderr , "Unsupported conversion from 444p10 to 420jpeg\n" ) ;
 return - 1 ;
 }
 }
 else if ( strcmp ( _y4m -> chroma_type , "444p12" ) == 0 ) {
 _y4m -> src_c_dec_h = 1 ;
 _y4m -> src_c_dec_v = 1 ;
 _y4m -> vpx_fmt = VPX_IMG_FMT_I44416 ;
 _y4m -> bps = 36 ;
 _y4m -> bit_depth = 12 ;
 _y4m -> dst_c_dec_h = _y4m -> src_c_dec_h ;
 _y4m -> dst_c_dec_v = _y4m -> src_c_dec_v ;
 _y4m -> dst_buf_read_sz = 2 * 3 * _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 0 ;
 _y4m -> convert = y4m_convert_null ;
 if ( only_420 ) {
 fprintf ( stderr , "Unsupported conversion from 444p12 to 420jpeg\n" ) ;
 return - 1 ;
 }
 }
 else if ( strcmp ( _y4m -> chroma_type , "444alpha" ) == 0 ) {
 _y4m -> src_c_dec_h = 1 ;
 _y4m -> src_c_dec_v = 1 ;
 if ( only_420 ) {
 _y4m -> dst_c_dec_h = 2 ;
 _y4m -> dst_c_dec_v = 2 ;
 _y4m -> dst_buf_read_sz = _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 3 * _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> convert = y4m_convert_444_420jpeg ;
 }
 else {
 _y4m -> vpx_fmt = VPX_IMG_FMT_444A ;
 _y4m -> bps = 32 ;
 _y4m -> dst_c_dec_h = _y4m -> src_c_dec_h ;
 _y4m -> dst_c_dec_v = _y4m -> src_c_dec_v ;
 _y4m -> dst_buf_read_sz = 4 * _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 0 ;
 _y4m -> convert = y4m_convert_null ;
 }
 }
 else if ( strcmp ( _y4m -> chroma_type , "mono" ) == 0 ) {
 _y4m -> src_c_dec_h = _y4m -> src_c_dec_v = 0 ;
 _y4m -> dst_c_dec_h = _y4m -> dst_c_dec_v = 2 ;
 _y4m -> dst_buf_read_sz = _y4m -> pic_w * _y4m -> pic_h ;
 _y4m -> aux_buf_sz = _y4m -> aux_buf_read_sz = 0 ;
 _y4m -> convert = y4m_convert_mono_420jpeg ;
 }
 else {
 fprintf ( stderr , "Unknown chroma sampling type: %s\n" , _y4m -> chroma_type ) ;
 return - 1 ;
 }
 _y4m -> dst_buf_sz = _y4m -> pic_w * _y4m -> pic_h + 2 * ( ( _y4m -> pic_w + _y4m -> dst_c_dec_h - 1 ) / _y4m -> dst_c_dec_h ) * ( ( _y4m -> pic_h + _y4m -> dst_c_dec_v - 1 ) / _y4m -> dst_c_dec_v ) ;
 if ( _y4m -> bit_depth == 8 ) _y4m -> dst_buf = ( unsigned char * ) malloc ( _y4m -> dst_buf_sz ) ;
 else _y4m -> dst_buf = ( unsigned char * ) malloc ( 2 * _y4m -> dst_buf_sz ) ;
 if ( _y4m -> aux_buf_sz > 0 ) _y4m -> aux_buf = ( unsigned char * ) malloc ( _y4m -> aux_buf_sz ) ;
 return 0 ;
 }