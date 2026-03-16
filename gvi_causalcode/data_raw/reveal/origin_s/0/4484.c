static gboolean ngsniffer_seek_read ( wtap * wth , gint64 seek_off , struct wtap_pkthdr * phdr , Buffer * buf , int * err , gchar * * err_info ) {
 int ret ;
 if ( ! ng_file_seek_rand ( wth , seek_off , err , err_info ) ) return FALSE ;
 ret = ngsniffer_process_record ( wth , TRUE , NULL , phdr , buf , err , err_info ) ;
 if ( ret < 0 ) {
 return FALSE ;
 }
 switch ( ret ) {
 case REC_FRAME2 : case REC_FRAME4 : case REC_FRAME6 : break ;
 default : g_assert_not_reached ( ) ;
 return FALSE ;
 }
 return TRUE ;
 }