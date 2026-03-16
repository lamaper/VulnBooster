static int dcc_resume_file_check ( FILE_DCC_REC * dcc , IRC_SERVER_REC * server , uoff_t size ) {
 if ( size >= dcc -> size ) {
 dcc -> starttime = time ( NULL ) ;
 dcc_reject ( DCC ( dcc ) , server ) ;
 }
 else if ( lseek ( dcc -> fhandle , ( off_t ) size , SEEK_SET ) != ( off_t ) size ) {
 dcc_reject ( DCC ( dcc ) , server ) ;
 }
 else {
 dcc -> transfd = dcc -> skipped = size ;
 return TRUE ;
 }
 return FALSE ;
 }