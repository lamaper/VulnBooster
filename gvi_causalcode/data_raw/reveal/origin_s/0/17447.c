void ArchiveEntry ( Archive * AHX , CatalogId catalogId , DumpId dumpId , const char * tag , const char * namespace , const char * tablespace , const char * owner , bool withOids , const char * desc , teSection section , const char * defn , const char * dropStmt , const char * copyStmt , const DumpId * deps , int nDeps , DataDumperPtr dumpFn , void * dumpArg ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 TocEntry * newToc ;
 newToc = ( TocEntry * ) pg_malloc0 ( sizeof ( TocEntry ) ) ;
 AH -> tocCount ++ ;
 if ( dumpId > AH -> maxDumpId ) AH -> maxDumpId = dumpId ;
 newToc -> prev = AH -> toc -> prev ;
 newToc -> next = AH -> toc ;
 AH -> toc -> prev -> next = newToc ;
 AH -> toc -> prev = newToc ;
 newToc -> catalogId = catalogId ;
 newToc -> dumpId = dumpId ;
 newToc -> section = section ;
 newToc -> tag = pg_strdup ( tag ) ;
 newToc -> namespace = namespace ? pg_strdup ( namespace ) : NULL ;
 newToc -> tablespace = tablespace ? pg_strdup ( tablespace ) : NULL ;
 newToc -> owner = pg_strdup ( owner ) ;
 newToc -> withOids = withOids ;
 newToc -> desc = pg_strdup ( desc ) ;
 newToc -> defn = pg_strdup ( defn ) ;
 newToc -> dropStmt = pg_strdup ( dropStmt ) ;
 newToc -> copyStmt = copyStmt ? pg_strdup ( copyStmt ) : NULL ;
 if ( nDeps > 0 ) {
 newToc -> dependencies = ( DumpId * ) pg_malloc ( nDeps * sizeof ( DumpId ) ) ;
 memcpy ( newToc -> dependencies , deps , nDeps * sizeof ( DumpId ) ) ;
 newToc -> nDeps = nDeps ;
 }
 else {
 newToc -> dependencies = NULL ;
 newToc -> nDeps = 0 ;
 }
 newToc -> dataDumper = dumpFn ;
 newToc -> dataDumperArg = dumpArg ;
 newToc -> hadDumper = dumpFn ? true : false ;
 newToc -> formatData = NULL ;
 if ( AH -> ArchiveEntryPtr != NULL ) ( * AH -> ArchiveEntryPtr ) ( AH , newToc ) ;
 }