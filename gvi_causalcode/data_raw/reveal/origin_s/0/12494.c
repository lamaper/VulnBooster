PGconn * GetConnection ( Archive * AHX ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 return AH -> connection ;
 }