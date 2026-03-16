static gboolean ngsniffer_read ( wtap * wth , int * err , gchar * * err_info , gint64 * data_offset ) {
 ngsniffer_t * ngsniffer ;
 int ret ;
 guint padding ;
 ngsniffer = ( ngsniffer_t * ) wth -> priv ;
 for ( ;
 ;
 ) {
 * data_offset = ngsniffer -> seq . uncomp_offset ;
 ret = ngsniffer_process_record ( wth , FALSE , & padding , & wth -> phdr , wth -> frame_buffer , err , err_info ) ;
 if ( ret < 0 ) {
 return FALSE ;
 }
 switch ( ret ) {
 case REC_FRAME2 : case REC_FRAME4 : case REC_FRAME6 : if ( padding != 0 ) {
 if ( ! ng_file_skip_seq ( wth , padding , err , err_info ) ) return FALSE ;
 }
 return TRUE ;
 case REC_EOF : * err = 0 ;
 return FALSE ;
 default : if ( padding != 0 ) {
 if ( ! ng_file_skip_seq ( wth , padding , err , err_info ) ) return FALSE ;
 }
 break ;
 }
 }
 }