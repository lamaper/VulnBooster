int ApplyBinaryPatch ( const wchar_t * old_file , const wchar_t * patch_file , const wchar_t * new_file ) {
 int ret = OK ;
 int ofd = - 1 ;
 int nfd = - 1 ;
 unsigned char * buf = NULL ;
 int pfd = _wopen ( patch_file , O_RDONLY | _O_BINARY ) ;
 if ( pfd < 0 ) return READ_ERROR ;
 do {
 MBSPatchHeader header ;
 if ( ( ret = MBS_ReadHeader ( pfd , & header ) ) ) break ;
 ofd = _wopen ( old_file , O_RDONLY | _O_BINARY ) ;
 if ( ofd < 0 ) {
 ret = READ_ERROR ;
 break ;
 }
 struct stat os ;
 if ( ( ret = fstat ( ofd , & os ) ) ) {
 ret = READ_ERROR ;
 break ;
 }
 if ( os . st_size != header . slen ) {
 ret = UNEXPECTED_ERROR ;
 break ;
 }
 buf = ( unsigned char * ) malloc ( header . slen ) ;
 if ( ! buf ) {
 ret = MEM_ERROR ;
 break ;
 }
 if ( read ( ofd , buf , header . slen ) != header . slen ) {
 ret = READ_ERROR ;
 break ;
 }
 if ( CalculateCrc ( buf , header . slen ) != header . scrc32 ) {
 ret = CRC_ERROR ;
 break ;
 }
 nfd = _wopen ( new_file , O_WRONLY | O_TRUNC | O_CREAT | _O_BINARY ) ;
 if ( nfd < 0 ) {
 ret = READ_ERROR ;
 break ;
 }
 ret = MBS_ApplyPatch ( & header , pfd , buf , nfd ) ;
 }
 while ( 0 ) ;
 free ( buf ) ;
 close ( pfd ) ;
 if ( ofd >= 0 ) close ( ofd ) ;
 if ( nfd >= 0 ) close ( nfd ) ;
 return ret ;
 }