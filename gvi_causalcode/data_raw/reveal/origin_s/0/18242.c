void ReadToc ( ArchiveHandle * AH ) {
 int i ;
 char * tmp ;
 DumpId * deps ;
 int depIdx ;
 int depSize ;
 TocEntry * te ;
 AH -> tocCount = ReadInt ( AH ) ;
 AH -> maxDumpId = 0 ;
 for ( i = 0 ;
 i < AH -> tocCount ;
 i ++ ) {
 te = ( TocEntry * ) pg_malloc0 ( sizeof ( TocEntry ) ) ;
 te -> dumpId = ReadInt ( AH ) ;
 if ( te -> dumpId > AH -> maxDumpId ) AH -> maxDumpId = te -> dumpId ;
 if ( te -> dumpId <= 0 ) exit_horribly ( modulename , "entry ID %d out of range -- perhaps a corrupt TOC\n" , te -> dumpId ) ;
 te -> hadDumper = ReadInt ( AH ) ;
 if ( AH -> version >= K_VERS_1_8 ) {
 tmp = ReadStr ( AH ) ;
 sscanf ( tmp , "%u" , & te -> catalogId . tableoid ) ;
 free ( tmp ) ;
 }
 else te -> catalogId . tableoid = InvalidOid ;
 tmp = ReadStr ( AH ) ;
 sscanf ( tmp , "%u" , & te -> catalogId . oid ) ;
 free ( tmp ) ;
 te -> tag = ReadStr ( AH ) ;
 te -> desc = ReadStr ( AH ) ;
 if ( AH -> version >= K_VERS_1_11 ) {
 te -> section = ReadInt ( AH ) ;
 }
 else {
 if ( strcmp ( te -> desc , "COMMENT" ) == 0 || strcmp ( te -> desc , "ACL" ) == 0 || strcmp ( te -> desc , "ACL LANGUAGE" ) == 0 ) te -> section = SECTION_NONE ;
 else if ( strcmp ( te -> desc , "TABLE DATA" ) == 0 || strcmp ( te -> desc , "BLOBS" ) == 0 || strcmp ( te -> desc , "BLOB COMMENTS" ) == 0 ) te -> section = SECTION_DATA ;
 else if ( strcmp ( te -> desc , "CONSTRAINT" ) == 0 || strcmp ( te -> desc , "CHECK CONSTRAINT" ) == 0 || strcmp ( te -> desc , "FK CONSTRAINT" ) == 0 || strcmp ( te -> desc , "INDEX" ) == 0 || strcmp ( te -> desc , "RULE" ) == 0 || strcmp ( te -> desc , "TRIGGER" ) == 0 ) te -> section = SECTION_POST_DATA ;
 else te -> section = SECTION_PRE_DATA ;
 }
 te -> defn = ReadStr ( AH ) ;
 te -> dropStmt = ReadStr ( AH ) ;
 if ( AH -> version >= K_VERS_1_3 ) te -> copyStmt = ReadStr ( AH ) ;
 if ( AH -> version >= K_VERS_1_6 ) te -> namespace = ReadStr ( AH ) ;
 if ( AH -> version >= K_VERS_1_10 ) te -> tablespace = ReadStr ( AH ) ;
 te -> owner = ReadStr ( AH ) ;
 if ( AH -> version >= K_VERS_1_9 ) {
 if ( strcmp ( ReadStr ( AH ) , "true" ) == 0 ) te -> withOids = true ;
 else te -> withOids = false ;
 }
 else te -> withOids = true ;
 if ( AH -> version >= K_VERS_1_5 ) {
 depSize = 100 ;
 deps = ( DumpId * ) pg_malloc ( sizeof ( DumpId ) * depSize ) ;
 depIdx = 0 ;
 for ( ;
 ;
 ) {
 tmp = ReadStr ( AH ) ;
 if ( ! tmp ) break ;
 if ( depIdx >= depSize ) {
 depSize *= 2 ;
 deps = ( DumpId * ) pg_realloc ( deps , sizeof ( DumpId ) * depSize ) ;
 }
 sscanf ( tmp , "%d" , & deps [ depIdx ] ) ;
 free ( tmp ) ;
 depIdx ++ ;
 }
 if ( depIdx > 0 ) {
 deps = ( DumpId * ) pg_realloc ( deps , sizeof ( DumpId ) * depIdx ) ;
 te -> dependencies = deps ;
 te -> nDeps = depIdx ;
 }
 else {
 free ( deps ) ;
 te -> dependencies = NULL ;
 te -> nDeps = 0 ;
 }
 }
 else {
 te -> dependencies = NULL ;
 te -> nDeps = 0 ;
 }
 if ( AH -> ReadExtraTocPtr ) ( * AH -> ReadExtraTocPtr ) ( AH , te ) ;
 ahlog ( AH , 3 , "read TOC entry %d (ID %d) for %s %s\n" , i , te -> dumpId , te -> desc , te -> tag ) ;
 te -> prev = AH -> toc -> prev ;
 AH -> toc -> prev -> next = te ;
 AH -> toc -> prev = te ;
 te -> next = AH -> toc ;
 if ( strcmp ( te -> desc , "ENCODING" ) == 0 ) processEncodingEntry ( AH , te ) ;
 else if ( strcmp ( te -> desc , "STDSTRINGS" ) == 0 ) processStdStringsEntry ( AH , te ) ;
 }
 }