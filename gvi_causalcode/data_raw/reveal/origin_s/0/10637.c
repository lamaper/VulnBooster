void ReadHead ( ArchiveHandle * AH ) {
 char tmpMag [ 7 ] ;
 int fmt ;
 struct tm crtm ;
 if ( ! AH -> readHeader ) {
 ( * AH -> ReadBufPtr ) ( AH , tmpMag , 5 ) ;
 if ( strncmp ( tmpMag , "PGDMP" , 5 ) != 0 ) exit_horribly ( modulename , "did not find magic string in file header\n" ) ;
 AH -> vmaj = ( * AH -> ReadBytePtr ) ( AH ) ;
 AH -> vmin = ( * AH -> ReadBytePtr ) ( AH ) ;
 if ( AH -> vmaj > 1 || ( ( AH -> vmaj == 1 ) && ( AH -> vmin > 0 ) ) ) AH -> vrev = ( * AH -> ReadBytePtr ) ( AH ) ;
 else AH -> vrev = 0 ;
 AH -> version = ( ( AH -> vmaj * 256 + AH -> vmin ) * 256 + AH -> vrev ) * 256 + 0 ;
 if ( AH -> version < K_VERS_1_0 || AH -> version > K_VERS_MAX ) exit_horribly ( modulename , "unsupported version (%d.%d) in file header\n" , AH -> vmaj , AH -> vmin ) ;
 AH -> intSize = ( * AH -> ReadBytePtr ) ( AH ) ;
 if ( AH -> intSize > 32 ) exit_horribly ( modulename , "sanity check on integer size (%lu) failed\n" , ( unsigned long ) AH -> intSize ) ;
 if ( AH -> intSize > sizeof ( int ) ) write_msg ( modulename , "WARNING: archive was made on a machine with larger integers, some operations might fail\n" ) ;
 if ( AH -> version >= K_VERS_1_7 ) AH -> offSize = ( * AH -> ReadBytePtr ) ( AH ) ;
 else AH -> offSize = AH -> intSize ;
 fmt = ( * AH -> ReadBytePtr ) ( AH ) ;
 if ( AH -> format != fmt ) exit_horribly ( modulename , "expected format (%d) differs from format found in file (%d)\n" , AH -> format , fmt ) ;
 }
 if ( AH -> version >= K_VERS_1_2 ) {
 if ( AH -> version < K_VERS_1_4 ) AH -> compression = ( * AH -> ReadBytePtr ) ( AH ) ;
 else AH -> compression = ReadInt ( AH ) ;
 }
 else AH -> compression = Z_DEFAULT_COMPRESSION ;


 crtm . tm_sec = ReadInt ( AH ) ;
 crtm . tm_min = ReadInt ( AH ) ;
 crtm . tm_hour = ReadInt ( AH ) ;
 crtm . tm_mday = ReadInt ( AH ) ;
 crtm . tm_mon = ReadInt ( AH ) ;
 crtm . tm_year = ReadInt ( AH ) ;
 crtm . tm_isdst = ReadInt ( AH ) ;
 AH -> archdbname = ReadStr ( AH ) ;
 AH -> createDate = mktime ( & crtm ) ;
 if ( AH -> createDate == ( time_t ) - 1 ) write_msg ( modulename , "WARNING: invalid creation date in header\n" ) ;
 }
 if ( AH -> version >= K_VERS_1_10 ) {
 AH -> archiveRemoteVersion = ReadStr ( AH ) ;
 AH -> archiveDumpVersion = ReadStr ( AH ) ;
 }
 }