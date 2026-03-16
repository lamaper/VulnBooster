static void fix_dependencies ( ArchiveHandle * AH ) {
 TocEntry * te ;
 int i ;
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 te -> depCount = te -> nDeps ;
 te -> revDeps = NULL ;
 te -> nRevDeps = 0 ;
 te -> par_prev = NULL ;
 te -> par_next = NULL ;
 }
 repoint_table_dependencies ( AH ) ;
 if ( AH -> version < K_VERS_1_11 ) {
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 if ( strcmp ( te -> desc , "BLOB COMMENTS" ) == 0 && te -> nDeps == 0 ) {
 TocEntry * te2 ;
 for ( te2 = AH -> toc -> next ;
 te2 != AH -> toc ;
 te2 = te2 -> next ) {
 if ( strcmp ( te2 -> desc , "BLOBS" ) == 0 ) {
 te -> dependencies = ( DumpId * ) pg_malloc ( sizeof ( DumpId ) ) ;
 te -> dependencies [ 0 ] = te2 -> dumpId ;
 te -> nDeps ++ ;
 te -> depCount ++ ;
 break ;
 }
 }
 break ;
 }
 }
 }
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 for ( i = 0 ;
 i < te -> nDeps ;
 i ++ ) {
 DumpId depid = te -> dependencies [ i ] ;
 if ( depid <= AH -> maxDumpId && AH -> tocsByDumpId [ depid ] != NULL ) AH -> tocsByDumpId [ depid ] -> nRevDeps ++ ;
 else te -> depCount -- ;
 }
 }
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 if ( te -> nRevDeps > 0 ) te -> revDeps = ( DumpId * ) pg_malloc ( te -> nRevDeps * sizeof ( DumpId ) ) ;
 te -> nRevDeps = 0 ;
 }
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 for ( i = 0 ;
 i < te -> nDeps ;
 i ++ ) {
 DumpId depid = te -> dependencies [ i ] ;
 if ( depid <= AH -> maxDumpId && AH -> tocsByDumpId [ depid ] != NULL ) {
 TocEntry * otherte = AH -> tocsByDumpId [ depid ] ;
 otherte -> revDeps [ otherte -> nRevDeps ++ ] = te -> dumpId ;
 }
 }
 }
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 te -> lockDeps = NULL ;
 te -> nLockDeps = 0 ;
 identify_locking_dependencies ( AH , te ) ;
 }
 }