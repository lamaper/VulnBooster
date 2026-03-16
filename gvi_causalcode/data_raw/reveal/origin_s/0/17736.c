TocEntry * getTocEntryByDumpId ( ArchiveHandle * AH , DumpId id ) {
 if ( AH -> tocsByDumpId == NULL ) buildTocEntryArrays ( AH ) ;
 if ( id > 0 && id <= AH -> maxDumpId ) return AH -> tocsByDumpId [ id ] ;
 return NULL ;
 }