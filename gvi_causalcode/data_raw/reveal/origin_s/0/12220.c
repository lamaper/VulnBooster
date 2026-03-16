static void k12_close ( wtap * wth ) {
 k12_t * k12 = ( k12_t * ) wth -> priv ;
 destroy_k12_file_data ( k12 ) ;
 wth -> priv = NULL ;

 if ( env_file ) fclose ( dbg_out ) ;
