static int _discoverArchiveFormat ( ArchiveHandle * AH ) {
 FILE * fh ;
 char sig [ 6 ] ;
 size_t cnt ;
 int wantClose = 0 ;


 AH -> lookaheadSize = 512 ;
 AH -> lookahead = pg_malloc0 ( 512 ) ;
 AH -> lookaheadLen = 0 ;
 AH -> lookaheadPos = 0 ;
 if ( AH -> fSpec ) {
 struct stat st ;
 wantClose = 1 ;
 if ( stat ( AH -> fSpec , & st ) == 0 && S_ISDIR ( st . st_mode ) ) {
 char buf [ MAXPGPATH ] ;
 if ( snprintf ( buf , MAXPGPATH , "%s/toc.dat" , AH -> fSpec ) >= MAXPGPATH ) exit_horribly ( modulename , "directory name too long: \"%s\"\n" , AH -> fSpec ) ;
 if ( stat ( buf , & st ) == 0 && S_ISREG ( st . st_mode ) ) {
 AH -> format = archDirectory ;
 return AH -> format ;
 }

 if ( stat ( buf , & st ) == 0 && S_ISREG ( st . st_mode ) ) {
 AH -> format = archDirectory ;
 return AH -> format ;
 }

 fh = NULL ;
 }
 else {
 fh = fopen ( AH -> fSpec , PG_BINARY_R ) ;
 if ( ! fh ) exit_horribly ( modulename , "could not open input file \"%s\": %s\n" , AH -> fSpec , strerror ( errno ) ) ;
 }
 }
 else {
 fh = stdin ;
 if ( ! fh ) exit_horribly ( modulename , "could not open input file: %s\n" , strerror ( errno ) ) ;
 }
 if ( ( cnt = fread ( sig , 1 , 5 , fh ) ) != 5 ) {
 if ( ferror ( fh ) ) exit_horribly ( modulename , "could not read input file: %s\n" , strerror ( errno ) ) ;
 else exit_horribly ( modulename , "input file is too short (read %lu, expected 5)\n" , ( unsigned long ) cnt ) ;
 }
 memcpy ( & AH -> lookahead [ 0 ] , sig , 5 ) ;
 AH -> lookaheadLen = 5 ;
 if ( strncmp ( sig , "PGDMP" , 5 ) == 0 ) {
 int byteread ;
 if ( ( byteread = fgetc ( fh ) ) == EOF ) READ_ERROR_EXIT ( fh ) ;
 AH -> vmaj = byteread ;
 if ( ( byteread = fgetc ( fh ) ) == EOF ) READ_ERROR_EXIT ( fh ) ;
 AH -> vmin = byteread ;
 AH -> lookahead [ AH -> lookaheadLen ++ ] = AH -> vmaj ;
 AH -> lookahead [ AH -> lookaheadLen ++ ] = AH -> vmin ;
 if ( AH -> vmaj > 1 || ( ( AH -> vmaj == 1 ) && ( AH -> vmin > 0 ) ) ) {
 if ( ( byteread = fgetc ( fh ) ) == EOF ) READ_ERROR_EXIT ( fh ) ;
 AH -> vrev = byteread ;
 AH -> lookahead [ AH -> lookaheadLen ++ ] = AH -> vrev ;
 }
 else AH -> vrev = 0 ;
 AH -> version = ( ( AH -> vmaj * 256 + AH -> vmin ) * 256 + AH -> vrev ) * 256 + 0 ;
 if ( ( AH -> intSize = fgetc ( fh ) ) == EOF ) READ_ERROR_EXIT ( fh ) ;
 AH -> lookahead [ AH -> lookaheadLen ++ ] = AH -> intSize ;
 if ( AH -> version >= K_VERS_1_7 ) {
 if ( ( AH -> offSize = fgetc ( fh ) ) == EOF ) READ_ERROR_EXIT ( fh ) ;
 AH -> lookahead [ AH -> lookaheadLen ++ ] = AH -> offSize ;
 }
 else AH -> offSize = AH -> intSize ;
 if ( ( byteread = fgetc ( fh ) ) == EOF ) READ_ERROR_EXIT ( fh ) ;
 AH -> format = byteread ;
 AH -> lookahead [ AH -> lookaheadLen ++ ] = AH -> format ;
 }
 else {
 cnt = fread ( & AH -> lookahead [ AH -> lookaheadLen ] , 1 , 512 - AH -> lookaheadLen , fh ) ;
 AH -> lookaheadLen += cnt ;
 if ( AH -> lookaheadLen >= strlen ( TEXT_DUMPALL_HEADER ) && ( strncmp ( AH -> lookahead , TEXT_DUMP_HEADER , strlen ( TEXT_DUMP_HEADER ) ) == 0 || strncmp ( AH -> lookahead , TEXT_DUMPALL_HEADER , strlen ( TEXT_DUMPALL_HEADER ) ) == 0 ) ) {
 exit_horribly ( modulename , "input file appears to be a text format dump. Please use psql.\n" ) ;
 }
 if ( AH -> lookaheadLen != 512 ) {
 if ( feof ( fh ) ) exit_horribly ( modulename , "input file does not appear to be a valid archive (too short?)\n" ) ;
 else READ_ERROR_EXIT ( fh ) ;
 }
 if ( ! isValidTarHeader ( AH -> lookahead ) ) exit_horribly ( modulename , "input file does not appear to be a valid archive\n" ) ;
 AH -> format = archTar ;
 }
 if ( fseeko ( fh , 0 , SEEK_SET ) != 0 ) {
 AH -> readHeader = 1 ;
 }
 else AH -> lookaheadLen = 0 ;
 if ( wantClose ) if ( fclose ( fh ) != 0 ) exit_horribly ( modulename , "could not close input file: %s\n" , strerror ( errno ) ) ;
 return AH -> format ;
 }