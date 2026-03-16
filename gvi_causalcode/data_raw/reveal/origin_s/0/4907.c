static void identify_locking_dependencies ( ArchiveHandle * AH , TocEntry * te ) {
 DumpId * lockids ;
 int nlockids ;
 int i ;
 if ( te -> nDeps == 0 ) return ;
 if ( ! ( strcmp ( te -> desc , "CONSTRAINT" ) == 0 || strcmp ( te -> desc , "CHECK CONSTRAINT" ) == 0 || strcmp ( te -> desc , "FK CONSTRAINT" ) == 0 || strcmp ( te -> desc , "RULE" ) == 0 || strcmp ( te -> desc , "TRIGGER" ) == 0 ) ) return ;
 lockids = ( DumpId * ) pg_malloc ( te -> nDeps * sizeof ( DumpId ) ) ;
 nlockids = 0 ;
 for ( i = 0 ;
 i < te -> nDeps ;
 i ++ ) {
 DumpId depid = te -> dependencies [ i ] ;
 if ( depid <= AH -> maxDumpId && AH -> tocsByDumpId [ depid ] != NULL && ( ( strcmp ( AH -> tocsByDumpId [ depid ] -> desc , "TABLE DATA" ) == 0 ) || strcmp ( AH -> tocsByDumpId [ depid ] -> desc , "TABLE" ) == 0 ) ) lockids [ nlockids ++ ] = depid ;
 }
 if ( nlockids == 0 ) {
 free ( lockids ) ;
 return ;
 }
 te -> lockDeps = pg_realloc ( lockids , nlockids * sizeof ( DumpId ) ) ;
 te -> nLockDeps = nlockids ;
 }