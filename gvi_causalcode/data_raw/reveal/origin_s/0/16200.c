void WriteHead ( ArchiveHandle * AH ) {
 struct tm crtm ;
 ( * AH -> WriteBufPtr ) ( AH , "PGDMP" , 5 ) ;
 ( * AH -> WriteBytePtr ) ( AH , AH -> vmaj ) ;
 ( * AH -> WriteBytePtr ) ( AH , AH -> vmin ) ;
 ( * AH -> WriteBytePtr ) ( AH , AH -> vrev ) ;
 ( * AH -> WriteBytePtr ) ( AH , AH -> intSize ) ;
 ( * AH -> WriteBytePtr ) ( AH , AH -> offSize ) ;
 ( * AH -> WriteBytePtr ) ( AH , AH -> format ) ;
 WriteInt ( AH , AH -> compression ) ;
 crtm = * localtime ( & AH -> createDate ) ;
 WriteInt ( AH , crtm . tm_sec ) ;
 WriteInt ( AH , crtm . tm_min ) ;
 WriteInt ( AH , crtm . tm_hour ) ;
 WriteInt ( AH , crtm . tm_mday ) ;
 WriteInt ( AH , crtm . tm_mon ) ;
 WriteInt ( AH , crtm . tm_year ) ;
 WriteInt ( AH , crtm . tm_isdst ) ;
 WriteStr ( AH , PQdb ( AH -> connection ) ) ;
 WriteStr ( AH , AH -> public . remoteVersionStr ) ;
 WriteStr ( AH , PG_VERSION ) ;
 }