void RestoreArchive ( Archive * AHX ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 RestoreOptions * ropt = AH -> public . ropt ;
 bool parallel_mode ;
 TocEntry * te ;
 OutputContext sav ;
 AH -> stage = STAGE_INITIALIZING ;
 if ( ropt -> createDB && ropt -> single_txn ) exit_horribly ( modulename , "-C and -1 are incompatible options\n" ) ;
 parallel_mode = ( AH -> public . numWorkers > 1 && ropt -> useDB ) ;
 if ( parallel_mode ) {
 if ( AH -> ClonePtr == NULL || AH -> ReopenPtr == NULL ) exit_horribly ( modulename , "parallel restore is not supported with this archive file format\n" ) ;
 if ( AH -> version < K_VERS_1_8 ) exit_horribly ( modulename , "parallel restore is not supported with archives made by pre-8.0 pg_dump\n" ) ;
 ( AH -> ReopenPtr ) ( AH ) ;
 }

 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 if ( te -> hadDumper && ( te -> reqs & REQ_DATA ) != 0 ) exit_horribly ( modulename , "cannot restore from compressed archive (compression not supported in this installation)\n" ) ;
 }
 }

 if ( ropt -> useDB ) {
 ahlog ( AH , 1 , "connecting to database for restore\n" ) ;
 if ( AH -> version < K_VERS_1_3 ) exit_horribly ( modulename , "direct database connections are not supported in pre-1.3 archives\n" ) ;
 AHX -> minRemoteVersion = 0 ;
 AHX -> maxRemoteVersion = 999999 ;
 ConnectDatabase ( AHX , ropt -> dbname , ropt -> pghost , ropt -> pgport , ropt -> username , ropt -> promptPassword ) ;
 AH -> noTocComments = 1 ;
 }
 if ( ! ropt -> dataOnly ) {
 int impliedDataOnly = 1 ;
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 if ( ( te -> reqs & REQ_SCHEMA ) != 0 ) {
 impliedDataOnly = 0 ;
 break ;
 }
 }
 if ( impliedDataOnly ) {
 ropt -> dataOnly = impliedDataOnly ;
 ahlog ( AH , 1 , "implied data-only restore\n" ) ;
 }
 }
 sav = SaveOutput ( AH ) ;
 if ( ropt -> filename || ropt -> compression ) SetOutput ( AH , ropt -> filename , ropt -> compression ) ;
 ahprintf ( AH , "--\n-- PostgreSQL database dump\n--\n\n" ) ;
 if ( AH -> archiveRemoteVersion ) ahprintf ( AH , "-- Dumped from database version %s\n" , AH -> archiveRemoteVersion ) ;
 if ( AH -> archiveDumpVersion ) ahprintf ( AH , "-- Dumped by pg_dump version %s\n" , AH -> archiveDumpVersion ) ;
 ahprintf ( AH , "\n" ) ;
 if ( AH -> public . verbose ) dumpTimestamp ( AH , "Started on" , AH -> createDate ) ;
 if ( ropt -> single_txn ) {
 if ( AH -> connection ) StartTransaction ( AHX ) ;
 else ahprintf ( AH , "BEGIN;
\n\n" ) ;
 }
 _doSetFixedOutputState ( AH ) ;
 AH -> stage = STAGE_PROCESSING ;
 if ( ropt -> dropSchema ) {
 for ( te = AH -> toc -> prev ;
 te != AH -> toc ;
 te = te -> prev ) {
 AH -> currentTE = te ;
 if ( ropt -> createDB ) {
 if ( strcmp ( te -> desc , "DATABASE" ) != 0 ) continue ;
 }
 else {
 if ( strcmp ( te -> desc , "DATABASE" ) == 0 ) continue ;
 }
 if ( ( ( te -> reqs & ( REQ_SCHEMA | REQ_DATA ) ) != 0 ) && te -> dropStmt ) {
 ahlog ( AH , 1 , "dropping %s %s\n" , te -> desc , te -> tag ) ;
 _becomeOwner ( AH , te ) ;
 _selectOutputSchema ( AH , te -> namespace ) ;
 if ( * te -> dropStmt != '\0' ) {
 if ( ! ropt -> if_exists ) {
 ahprintf ( AH , "%s" , te -> dropStmt ) ;
 }
 else {
 if ( strncmp ( te -> desc , "BLOB" , 4 ) == 0 ) {
 DropBlobIfExists ( AH , te -> catalogId . oid ) ;
 }
 else {
 char buffer [ 40 ] ;
 char * mark ;
 char * dropStmt = pg_strdup ( te -> dropStmt ) ;
 char * dropStmtPtr = dropStmt ;
 PQExpBuffer ftStmt = createPQExpBuffer ( ) ;
 if ( strncmp ( dropStmt , "ALTER TABLE" , 11 ) == 0 ) {
 appendPQExpBuffer ( ftStmt , "ALTER TABLE IF EXISTS" ) ;
 dropStmt = dropStmt + 11 ;
 }
 if ( strcmp ( te -> desc , "DEFAULT" ) == 0 ) appendPQExpBufferStr ( ftStmt , dropStmt ) ;
 else {
 if ( strcmp ( te -> desc , "CONSTRAINT" ) == 0 || strcmp ( te -> desc , "CHECK CONSTRAINT" ) == 0 || strcmp ( te -> desc , "FK CONSTRAINT" ) == 0 ) strcpy ( buffer , "DROP CONSTRAINT" ) ;
 else snprintf ( buffer , sizeof ( buffer ) , "DROP %s" , te -> desc ) ;
 mark = strstr ( dropStmt , buffer ) ;
 Assert ( mark != NULL ) ;
 * mark = '\0' ;
 appendPQExpBuffer ( ftStmt , "%s%s IF EXISTS%s" , dropStmt , buffer , mark + strlen ( buffer ) ) ;
 }
 ahprintf ( AH , "%s" , ftStmt -> data ) ;
 destroyPQExpBuffer ( ftStmt ) ;
 pg_free ( dropStmtPtr ) ;
 }
 }
 }
 }
 }
 if ( AH -> currSchema ) free ( AH -> currSchema ) ;
 AH -> currSchema = NULL ;
 }
 if ( parallel_mode ) {
 ParallelState * pstate ;
 TocEntry pending_list ;
 par_list_header_init ( & pending_list ) ;
 restore_toc_entries_prefork ( AH ) ;
 Assert ( AH -> connection == NULL ) ;
 pstate = ParallelBackupStart ( AH ) ;
 restore_toc_entries_parallel ( AH , pstate , & pending_list ) ;
 ParallelBackupEnd ( AH , pstate ) ;
 restore_toc_entries_postfork ( AH , & pending_list ) ;
 Assert ( AH -> connection != NULL ) ;
 }
 else {
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) ( void ) restore_toc_entry ( AH , te , false ) ;
 }
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 AH -> currentTE = te ;
 if ( ( te -> reqs & ( REQ_SCHEMA | REQ_DATA ) ) != 0 ) {
 if ( te -> namespace ) ahlog ( AH , 1 , "setting owner and privileges for %s \"%s.%s\"\n" , te -> desc , te -> namespace , te -> tag ) ;
 else ahlog ( AH , 1 , "setting owner and privileges for %s \"%s\"\n" , te -> desc , te -> tag ) ;
 _printTocEntry ( AH , te , false , true ) ;
 }
 }
 if ( ropt -> single_txn ) {
 if ( AH -> connection ) CommitTransaction ( AHX ) ;
 else ahprintf ( AH , "COMMIT;
\n\n" ) ;
 }
 if ( AH -> public . verbose ) dumpTimestamp ( AH , "Completed on" , time ( NULL ) ) ;
 ahprintf ( AH , "--\n-- PostgreSQL database dump complete\n--\n\n" ) ;
 AH -> stage = STAGE_FINALIZING ;
 if ( ropt -> filename || ropt -> compression ) RestoreOutput ( AH , sav ) ;
 if ( ropt -> useDB ) DisconnectDatabase ( & AH -> public ) ;
 }