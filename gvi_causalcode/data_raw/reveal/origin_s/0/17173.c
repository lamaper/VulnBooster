static void dcc_send_resume ( GET_DCC_REC * dcc ) {
 off_t pos ;
 char * str ;
 g_return_if_fail ( dcc != NULL ) ;
 dcc -> file = dcc_get_download_path ( dcc -> arg ) ;
 dcc -> fhandle = open ( dcc -> file , O_WRONLY ) ;
 if ( dcc -> fhandle == - 1 ) {
 signal_emit ( "dcc error file open" , 3 , dcc -> nick , dcc -> file , GINT_TO_POINTER ( errno ) ) ;
 return ;
 }
 dcc -> get_type = DCC_GET_RESUME ;
 pos = lseek ( dcc -> fhandle , 0 , SEEK_END ) ;
 dcc -> transfd = pos < 0 ? 0 : ( uoff_t ) pos ;
 dcc -> skipped = dcc -> transfd ;
 if ( dcc -> skipped == dcc -> size ) {
 dcc -> starttime = time ( NULL ) ;
 dcc_reject ( DCC ( dcc ) , NULL ) ;
 }
 else {
 if ( ! dcc_is_passive ( dcc ) ) {
 str = g_strdup_printf ( dcc -> file_quoted ? "DCC RESUME \"%s\" %d %" PRIuUOFF_T : "DCC RESUME %s %d %" PRIuUOFF_T , dcc -> arg , dcc -> port , dcc -> transfd ) ;
 }
 else {
 str = g_strdup_printf ( dcc -> file_quoted ? "DCC RESUME \"%s\" 0 %" PRIuUOFF_T " %d" : "DCC RESUME %s 0 %" PRIuUOFF_T " %d" , dcc -> arg , dcc -> transfd , dcc -> pasv_id ) ;
 }
 dcc_ctcp_message ( dcc -> server , dcc -> nick , dcc -> chat , FALSE , str ) ;
 g_free ( str ) ;
 }
 }