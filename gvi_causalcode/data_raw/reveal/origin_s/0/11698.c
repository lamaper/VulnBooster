static int matroska_read_header ( AVFormatContext * s ) {
 MatroskaDemuxContext * matroska = s -> priv_data ;
 EbmlList * attachments_list = & matroska -> attachments ;
 EbmlList * chapters_list = & matroska -> chapters ;
 MatroskaAttachment * attachments ;
 MatroskaChapter * chapters ;
 uint64_t max_start = 0 ;
 int64_t pos ;
 Ebml ebml = {
 0 }
 ;
 int i , j , res ;
 matroska -> ctx = s ;
 if ( ebml_parse ( matroska , ebml_syntax , & ebml ) || ebml . version > EBML_VERSION || ebml . max_size > sizeof ( uint64_t ) || ebml . id_length > sizeof ( uint32_t ) || ebml . doctype_version > 3 ) {
 av_log ( matroska -> ctx , AV_LOG_ERROR , "EBML header using unsupported features\n" "(EBML version %" PRIu64 ", doctype %s, doc version %" PRIu64 ")\n" , ebml . version , ebml . doctype , ebml . doctype_version ) ;
 ebml_free ( ebml_syntax , & ebml ) ;
 return AVERROR_PATCHWELCOME ;
 }
 for ( i = 0 ;
 i < FF_ARRAY_ELEMS ( matroska_doctypes ) ;
 i ++ ) if ( ! strcmp ( ebml . doctype , matroska_doctypes [ i ] ) ) break ;
 if ( i >= FF_ARRAY_ELEMS ( matroska_doctypes ) ) {
 av_log ( s , AV_LOG_WARNING , "Unknown EBML doctype '%s'\n" , ebml . doctype ) ;
 if ( matroska -> ctx -> error_recognition & AV_EF_EXPLODE ) {
 ebml_free ( ebml_syntax , & ebml ) ;
 return AVERROR_INVALIDDATA ;
 }
 }
 ebml_free ( ebml_syntax , & ebml ) ;
 pos = avio_tell ( matroska -> ctx -> pb ) ;
 res = ebml_parse ( matroska , matroska_segments , matroska ) ;
 while ( res != 1 ) {
 res = matroska_resync ( matroska , pos ) ;
 if ( res < 0 ) return res ;
 pos = avio_tell ( matroska -> ctx -> pb ) ;
 res = ebml_parse ( matroska , matroska_segment , matroska ) ;
 }
 matroska_execute_seekhead ( matroska ) ;
 if ( ! matroska -> time_scale ) matroska -> time_scale = 1000000 ;
 if ( matroska -> duration ) matroska -> ctx -> duration = matroska -> duration * matroska -> time_scale * 1000 / AV_TIME_BASE ;
 av_dict_set ( & s -> metadata , "title" , matroska -> title , 0 ) ;
 res = matroska_parse_tracks ( s ) ;
 if ( res < 0 ) return res ;
 attachments = attachments_list -> elem ;
 for ( j = 0 ;
 j < attachments_list -> nb_elem ;
 j ++ ) {
 if ( ! ( attachments [ j ] . filename && attachments [ j ] . mime && attachments [ j ] . bin . data && attachments [ j ] . bin . size > 0 ) ) {
 av_log ( matroska -> ctx , AV_LOG_ERROR , "incomplete attachment\n" ) ;
 }
 else {
 AVStream * st = avformat_new_stream ( s , NULL ) ;
 if ( ! st ) break ;
 av_dict_set ( & st -> metadata , "filename" , attachments [ j ] . filename , 0 ) ;
 av_dict_set ( & st -> metadata , "mimetype" , attachments [ j ] . mime , 0 ) ;
 st -> codec -> codec_id = AV_CODEC_ID_NONE ;
 st -> codec -> codec_type = AVMEDIA_TYPE_ATTACHMENT ;
 st -> codec -> extradata = av_malloc ( attachments [ j ] . bin . size ) ;
 if ( ! st -> codec -> extradata ) break ;
 st -> codec -> extradata_size = attachments [ j ] . bin . size ;
 memcpy ( st -> codec -> extradata , attachments [ j ] . bin . data , attachments [ j ] . bin . size ) ;
 for ( i = 0 ;
 ff_mkv_mime_tags [ i ] . id != AV_CODEC_ID_NONE ;
 i ++ ) {
 if ( ! strncmp ( ff_mkv_mime_tags [ i ] . str , attachments [ j ] . mime , strlen ( ff_mkv_mime_tags [ i ] . str ) ) ) {
 st -> codec -> codec_id = ff_mkv_mime_tags [ i ] . id ;
 break ;
 }
 }
 attachments [ j ] . stream = st ;
 }
 }
 chapters = chapters_list -> elem ;
 for ( i = 0 ;
 i < chapters_list -> nb_elem ;
 i ++ ) if ( chapters [ i ] . start != AV_NOPTS_VALUE && chapters [ i ] . uid && ( max_start == 0 || chapters [ i ] . start > max_start ) ) {
 chapters [ i ] . chapter = avpriv_new_chapter ( s , chapters [ i ] . uid , ( AVRational ) {
 1 , 1000000000 }
 , chapters [ i ] . start , chapters [ i ] . end , chapters [ i ] . title ) ;
 av_dict_set ( & chapters [ i ] . chapter -> metadata , "title" , chapters [ i ] . title , 0 ) ;
 max_start = chapters [ i ] . start ;
 }
 matroska_convert_tags ( s ) ;
 return 0 ;
 }