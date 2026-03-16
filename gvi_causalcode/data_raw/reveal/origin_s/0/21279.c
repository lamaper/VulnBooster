static gboolean logcat_read ( wtap * wth , int * err , gchar * * err_info , gint64 * data_offset ) {
 * data_offset = file_tell ( wth -> fh ) ;
 return logcat_read_packet ( ( struct logcat_phdr * ) wth -> priv , wth -> fh , & wth -> phdr , wth -> frame_buffer , err , err_info ) ;
 }