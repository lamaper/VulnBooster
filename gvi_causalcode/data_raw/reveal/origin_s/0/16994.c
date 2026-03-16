int logcat_open ( wtap * wth , int * err , gchar * * err_info _U_ ) {
 int local_err ;
 gchar * local_err_info ;
 gint version ;
 gint tmp_version ;
 struct logcat_phdr * logcat ;
 version = detect_version ( wth , & local_err , & local_err_info ) ;
 if ( version <= 0 ) return 0 ;
 tmp_version = detect_version ( wth , & local_err , & local_err_info ) ;
 if ( tmp_version < 0 && ! file_eof ( wth -> fh ) ) {
 return 0 ;
 }
 else if ( tmp_version > 0 ) {
 if ( tmp_version != version ) return 0 ;
 tmp_version = detect_version ( wth , & local_err , & local_err_info ) ;
 if ( tmp_version != version && ! file_eof ( wth -> fh ) ) return 0 ;
 }
 if ( file_seek ( wth -> fh , 0 , SEEK_SET , err ) == - 1 ) return - 1 ;
 logcat = ( struct logcat_phdr * ) g_malloc ( sizeof ( struct logcat_phdr ) ) ;
 logcat -> version = version ;
 wth -> priv = logcat ;
 wth -> file_type_subtype = WTAP_FILE_TYPE_SUBTYPE_LOGCAT ;
 wth -> file_encap = WTAP_ENCAP_LOGCAT ;
 wth -> snapshot_length = 0 ;
 wth -> subtype_read = logcat_read ;
 wth -> subtype_seek_read = logcat_seek_read ;
 wth -> tsprecision = WTAP_FILE_TSPREC_USEC ;
 return 1 ;
 }