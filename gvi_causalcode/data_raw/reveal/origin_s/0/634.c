static int matroska_parse_tracks ( AVFormatContext * s ) {
 MatroskaDemuxContext * matroska = s -> priv_data ;
 MatroskaTrack * tracks = matroska -> tracks . elem ;
 AVStream * st ;
 int i , j , ret ;
 for ( i = 0 ;
 i < matroska -> tracks . nb_elem ;
 i ++ ) {
 MatroskaTrack * track = & tracks [ i ] ;
 enum AVCodecID codec_id = AV_CODEC_ID_NONE ;
 EbmlList * encodings_list = & track -> encodings ;
 MatroskaTrackEncoding * encodings = encodings_list -> elem ;
 uint8_t * extradata = NULL ;
 int extradata_size = 0 ;
 int extradata_offset = 0 ;
 AVIOContext b ;
 if ( track -> type != MATROSKA_TRACK_TYPE_VIDEO && track -> type != MATROSKA_TRACK_TYPE_AUDIO && track -> type != MATROSKA_TRACK_TYPE_SUBTITLE ) {
 av_log ( matroska -> ctx , AV_LOG_INFO , "Unknown or unsupported track type %" PRIu64 "\n" , track -> type ) ;
 continue ;
 }
 if ( ! track -> codec_id ) continue ;
 if ( track -> type == MATROSKA_TRACK_TYPE_VIDEO ) {
 if ( ! track -> default_duration && track -> video . frame_rate > 0 ) track -> default_duration = 1000000000 / track -> video . frame_rate ;
 if ( ! track -> video . display_width ) track -> video . display_width = track -> video . pixel_width ;
 if ( ! track -> video . display_height ) track -> video . display_height = track -> video . pixel_height ;
 }
 else if ( track -> type == MATROSKA_TRACK_TYPE_AUDIO ) {
 if ( ! track -> audio . out_samplerate ) track -> audio . out_samplerate = track -> audio . samplerate ;
 }
 if ( encodings_list -> nb_elem > 1 ) {
 av_log ( matroska -> ctx , AV_LOG_ERROR , "Multiple combined encodings not supported" ) ;
 }
 else if ( encodings_list -> nb_elem == 1 ) {
 if ( encodings [ 0 ] . type || ( # if CONFIG_ZLIB encodings [ 0 ] . compression . algo != MATROSKA_TRACK_ENCODING_COMP_ZLIB && # endif # if CONFIG_BZLIB encodings [ 0 ] . compression . algo != MATROSKA_TRACK_ENCODING_COMP_BZLIB && # endif # if CONFIG_LZO encodings [ 0 ] . compression . algo != MATROSKA_TRACK_ENCODING_COMP_LZO && # endif encodings [ 0 ] . compression . algo != MATROSKA_TRACK_ENCODING_COMP_HEADERSTRIP ) ) {
 encodings [ 0 ] . scope = 0 ;
 av_log ( matroska -> ctx , AV_LOG_ERROR , "Unsupported encoding type" ) ;
 }
 else if ( track -> codec_priv . size && encodings [ 0 ] . scope & 2 ) {
 uint8_t * codec_priv = track -> codec_priv . data ;
 int ret = matroska_decode_buffer ( & track -> codec_priv . data , & track -> codec_priv . size , track ) ;
 if ( ret < 0 ) {
 track -> codec_priv . data = NULL ;
 track -> codec_priv . size = 0 ;
 av_log ( matroska -> ctx , AV_LOG_ERROR , "Failed to decode codec private data\n" ) ;
 }
 if ( codec_priv != track -> codec_priv . data ) av_free ( codec_priv ) ;
 }
 }
 for ( j = 0 ;
 ff_mkv_codec_tags [ j ] . id != AV_CODEC_ID_NONE ;
 j ++ ) {
 if ( ! strncmp ( ff_mkv_codec_tags [ j ] . str , track -> codec_id , strlen ( ff_mkv_codec_tags [ j ] . str ) ) ) {
 codec_id = ff_mkv_codec_tags [ j ] . id ;
 break ;
 }
 }
 st = track -> stream = avformat_new_stream ( s , NULL ) ;
 if ( ! st ) return AVERROR ( ENOMEM ) ;
 if ( ! strcmp ( track -> codec_id , "V_MS/VFW/FOURCC" ) && track -> codec_priv . size >= 40 && track -> codec_priv . data ) {
 track -> ms_compat = 1 ;
 track -> video . fourcc = AV_RL32 ( track -> codec_priv . data + 16 ) ;
 codec_id = ff_codec_get_id ( ff_codec_bmp_tags , track -> video . fourcc ) ;
 extradata_offset = 40 ;
 }
 else if ( ! strcmp ( track -> codec_id , "A_MS/ACM" ) && track -> codec_priv . size >= 14 && track -> codec_priv . data ) {
 int ret ;
 ffio_init_context ( & b , track -> codec_priv . data , track -> codec_priv . size , 0 , NULL , NULL , NULL , NULL ) ;
 ret = ff_get_wav_header ( & b , st -> codec , track -> codec_priv . size ) ;
 if ( ret < 0 ) return ret ;
 codec_id = st -> codec -> codec_id ;
 extradata_offset = FFMIN ( track -> codec_priv . size , 18 ) ;
 }
 else if ( ! strcmp ( track -> codec_id , "V_QUICKTIME" ) && ( track -> codec_priv . size >= 86 ) && ( track -> codec_priv . data ) ) {
 track -> video . fourcc = AV_RL32 ( track -> codec_priv . data ) ;
 codec_id = ff_codec_get_id ( ff_codec_movvideo_tags , track -> video . fourcc ) ;
 }
 else if ( codec_id == AV_CODEC_ID_PCM_S16BE ) {
 switch ( track -> audio . bitdepth ) {
 case 8 : codec_id = AV_CODEC_ID_PCM_U8 ;
 break ;
 case 24 : codec_id = AV_CODEC_ID_PCM_S24BE ;
 break ;
 case 32 : codec_id = AV_CODEC_ID_PCM_S32BE ;
 break ;
 }
 }
 else if ( codec_id == AV_CODEC_ID_PCM_S16LE ) {
 switch ( track -> audio . bitdepth ) {
 case 8 : codec_id = AV_CODEC_ID_PCM_U8 ;
 break ;
 case 24 : codec_id = AV_CODEC_ID_PCM_S24LE ;
 break ;
 case 32 : codec_id = AV_CODEC_ID_PCM_S32LE ;
 break ;
 }
 }
 else if ( codec_id == AV_CODEC_ID_PCM_F32LE && track -> audio . bitdepth == 64 ) {
 codec_id = AV_CODEC_ID_PCM_F64LE ;
 }
 else if ( codec_id == AV_CODEC_ID_AAC && ! track -> codec_priv . size ) {
 int profile = matroska_aac_profile ( track -> codec_id ) ;
 int sri = matroska_aac_sri ( track -> audio . samplerate ) ;
 extradata = av_mallocz ( 5 + FF_INPUT_BUFFER_PADDING_SIZE ) ;
 if ( ! extradata ) return AVERROR ( ENOMEM ) ;
 extradata [ 0 ] = ( profile << 3 ) | ( ( sri & 0x0E ) >> 1 ) ;
 extradata [ 1 ] = ( ( sri & 0x01 ) << 7 ) | ( track -> audio . channels << 3 ) ;
 if ( strstr ( track -> codec_id , "SBR" ) ) {
 sri = matroska_aac_sri ( track -> audio . out_samplerate ) ;
 extradata [ 2 ] = 0x56 ;
 extradata [ 3 ] = 0xE5 ;
 extradata [ 4 ] = 0x80 | ( sri << 3 ) ;
 extradata_size = 5 ;
 }
 else extradata_size = 2 ;
 }
 else if ( codec_id == AV_CODEC_ID_ALAC && track -> codec_priv . size ) {
 extradata_size = 12 + track -> codec_priv . size ;
 extradata = av_mallocz ( extradata_size + FF_INPUT_BUFFER_PADDING_SIZE ) ;
 if ( ! extradata ) return AVERROR ( ENOMEM ) ;
 AV_WB32 ( extradata , extradata_size ) ;
 memcpy ( & extradata [ 4 ] , "alac" , 4 ) ;
 AV_WB32 ( & extradata [ 8 ] , 0 ) ;
 memcpy ( & extradata [ 12 ] , track -> codec_priv . data , track -> codec_priv . size ) ;
 }
 else if ( codec_id == AV_CODEC_ID_TTA ) {
 extradata_size = 30 ;
 extradata = av_mallocz ( extradata_size ) ;
 if ( ! extradata ) return AVERROR ( ENOMEM ) ;
 ffio_init_context ( & b , extradata , extradata_size , 1 , NULL , NULL , NULL , NULL ) ;
 avio_write ( & b , "TTA1" , 4 ) ;
 avio_wl16 ( & b , 1 ) ;
 avio_wl16 ( & b , track -> audio . channels ) ;
 avio_wl16 ( & b , track -> audio . bitdepth ) ;
 avio_wl32 ( & b , track -> audio . out_samplerate ) ;
 avio_wl32 ( & b , matroska -> ctx -> duration * track -> audio . out_samplerate ) ;
 }
 else if ( codec_id == AV_CODEC_ID_RV10 || codec_id == AV_CODEC_ID_RV20 || codec_id == AV_CODEC_ID_RV30 || codec_id == AV_CODEC_ID_RV40 ) {
 extradata_offset = 26 ;
 }
 else if ( codec_id == AV_CODEC_ID_RA_144 ) {
 track -> audio . out_samplerate = 8000 ;
 track -> audio . channels = 1 ;
 }
 else if ( codec_id == AV_CODEC_ID_RA_288 || codec_id == AV_CODEC_ID_COOK || codec_id == AV_CODEC_ID_ATRAC3 || codec_id == AV_CODEC_ID_SIPR ) {
 int flavor ;
 ffio_init_context ( & b , track -> codec_priv . data , track -> codec_priv . size , 0 , NULL , NULL , NULL , NULL ) ;
 avio_skip ( & b , 22 ) ;
 flavor = avio_rb16 ( & b ) ;
 track -> audio . coded_framesize = avio_rb32 ( & b ) ;
 avio_skip ( & b , 12 ) ;
 track -> audio . sub_packet_h = avio_rb16 ( & b ) ;
 track -> audio . frame_size = avio_rb16 ( & b ) ;
 track -> audio . sub_packet_size = avio_rb16 ( & b ) ;
 if ( flavor <= 0 || track -> audio . coded_framesize <= 0 || track -> audio . sub_packet_h <= 0 || track -> audio . frame_size <= 0 || track -> audio . sub_packet_size <= 0 ) return AVERROR_INVALIDDATA ;
 track -> audio . buf = av_malloc ( track -> audio . frame_size * track -> audio . sub_packet_h ) ;
 if ( codec_id == AV_CODEC_ID_RA_288 ) {
 st -> codec -> block_align = track -> audio . coded_framesize ;
 track -> codec_priv . size = 0 ;
 }
 else {
 if ( codec_id == AV_CODEC_ID_SIPR && flavor < 4 ) {
 const int sipr_bit_rate [ 4 ] = {
 6504 , 8496 , 5000 , 16000 }
 ;
 track -> audio . sub_packet_size = ff_sipr_subpk_size [ flavor ] ;
 st -> codec -> bit_rate = sipr_bit_rate [ flavor ] ;
 }
 st -> codec -> block_align = track -> audio . sub_packet_size ;
 extradata_offset = 78 ;
 }
 }
 else if ( codec_id == AV_CODEC_ID_FLAC && track -> codec_priv . size ) {
 ret = matroska_parse_flac ( s , track , & extradata_offset ) ;
 if ( ret < 0 ) return ret ;
 }
 track -> codec_priv . size -= extradata_offset ;
 if ( codec_id == AV_CODEC_ID_NONE ) av_log ( matroska -> ctx , AV_LOG_INFO , "Unknown/unsupported AVCodecID %s.\n" , track -> codec_id ) ;
 if ( track -> time_scale < 0.01 ) track -> time_scale = 1.0 ;
 avpriv_set_pts_info ( st , 64 , matroska -> time_scale * track -> time_scale , 1000 * 1000 * 1000 ) ;
 track -> codec_delay = av_rescale_q ( track -> codec_delay , ( AVRational ) {
 1 , 1000000000 }
 , st -> time_base ) ;
 st -> codec -> codec_id = codec_id ;
 st -> start_time = 0 ;
 if ( strcmp ( track -> language , "und" ) ) av_dict_set ( & st -> metadata , "language" , track -> language , 0 ) ;
 av_dict_set ( & st -> metadata , "title" , track -> name , 0 ) ;
 if ( track -> flag_default ) st -> disposition |= AV_DISPOSITION_DEFAULT ;
 if ( track -> flag_forced ) st -> disposition |= AV_DISPOSITION_FORCED ;
 if ( ! st -> codec -> extradata ) {
 if ( extradata ) {
 st -> codec -> extradata = extradata ;
 st -> codec -> extradata_size = extradata_size ;
 }
 else if ( track -> codec_priv . data && track -> codec_priv . size > 0 ) {
 st -> codec -> extradata = av_mallocz ( track -> codec_priv . size + FF_INPUT_BUFFER_PADDING_SIZE ) ;
 if ( ! st -> codec -> extradata ) return AVERROR ( ENOMEM ) ;
 st -> codec -> extradata_size = track -> codec_priv . size ;
 memcpy ( st -> codec -> extradata , track -> codec_priv . data + extradata_offset , track -> codec_priv . size ) ;
 }
 }
 if ( track -> type == MATROSKA_TRACK_TYPE_VIDEO ) {
 st -> codec -> codec_type = AVMEDIA_TYPE_VIDEO ;
 st -> codec -> codec_tag = track -> video . fourcc ;
 st -> codec -> width = track -> video . pixel_width ;
 st -> codec -> height = track -> video . pixel_height ;
 av_reduce ( & st -> sample_aspect_ratio . num , & st -> sample_aspect_ratio . den , st -> codec -> height * track -> video . display_width , st -> codec -> width * track -> video . display_height , 255 ) ;
 if ( st -> codec -> codec_id != AV_CODEC_ID_H264 && st -> codec -> codec_id != AV_CODEC_ID_HEVC ) st -> need_parsing = AVSTREAM_PARSE_HEADERS ;
 if ( track -> default_duration ) {
 av_reduce ( & st -> avg_frame_rate . num , & st -> avg_frame_rate . den , 1000000000 , track -> default_duration , 30000 ) ;
 }
 if ( track -> video . stereo_mode < MATROSKA_VIDEO_STEREOMODE_TYPE_NB && track -> video . stereo_mode != 10 && track -> video . stereo_mode != 12 ) {
 int ret = ff_mkv_stereo3d_conv ( st , track -> video . stereo_mode ) ;
 if ( ret < 0 ) return ret ;
 }
 }
 else if ( track -> type == MATROSKA_TRACK_TYPE_AUDIO ) {
 st -> codec -> codec_type = AVMEDIA_TYPE_AUDIO ;
 st -> codec -> sample_rate = track -> audio . out_samplerate ;
 st -> codec -> channels = track -> audio . channels ;
 if ( st -> codec -> codec_id != AV_CODEC_ID_AAC ) st -> need_parsing = AVSTREAM_PARSE_HEADERS ;
 }
 else if ( track -> type == MATROSKA_TRACK_TYPE_SUBTITLE ) {
 st -> codec -> codec_type = AVMEDIA_TYPE_SUBTITLE ;
 if ( st -> codec -> codec_id == AV_CODEC_ID_SSA ) matroska -> contains_ssa = 1 ;
 }
 }
 return 0 ;
 }