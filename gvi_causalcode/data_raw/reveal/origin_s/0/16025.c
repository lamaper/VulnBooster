void SortTocFromFile ( Archive * AHX ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 RestoreOptions * ropt = AH -> public . ropt ;
 FILE * fh ;
 char buf [ 100 ] ;
 bool incomplete_line ;
 ropt -> idWanted = ( bool * ) pg_malloc ( sizeof ( bool ) * AH -> maxDumpId ) ;
 memset ( ropt -> idWanted , 0 , sizeof ( bool ) * AH -> maxDumpId ) ;
 fh = fopen ( ropt -> tocFile , PG_BINARY_R ) ;
 if ( ! fh ) exit_horribly ( modulename , "could not open TOC file \"%s\": %s\n" , ropt -> tocFile , strerror ( errno ) ) ;
 incomplete_line = false ;
 while ( fgets ( buf , sizeof ( buf ) , fh ) != NULL ) {
 bool prev_incomplete_line = incomplete_line ;
 int buflen ;
 char * cmnt ;
 char * endptr ;
 DumpId id ;
 TocEntry * te ;
 buflen = strlen ( buf ) ;
 if ( buflen > 0 && buf [ buflen - 1 ] == '\n' ) incomplete_line = false ;
 else incomplete_line = true ;
 if ( prev_incomplete_line ) continue ;
 cmnt = strchr ( buf , ';
' ) ;
 if ( cmnt != NULL ) cmnt [ 0 ] = '\0' ;
 if ( strspn ( buf , " \t\r\n" ) == strlen ( buf ) ) continue ;
 id = strtol ( buf , & endptr , 10 ) ;
 if ( endptr == buf || id <= 0 || id > AH -> maxDumpId || ropt -> idWanted [ id - 1 ] ) {
 write_msg ( modulename , "WARNING: line ignored: %s\n" , buf ) ;
 continue ;
 }
 te = getTocEntryByDumpId ( AH , id ) ;
 if ( ! te ) exit_horribly ( modulename , "could not find entry for ID %d\n" , id ) ;
 ropt -> idWanted [ id - 1 ] = true ;
 _moveBefore ( AH , AH -> toc , te ) ;
 }
 if ( fclose ( fh ) != 0 ) exit_horribly ( modulename , "could not close TOC file: %s\n" , strerror ( errno ) ) ;
 }