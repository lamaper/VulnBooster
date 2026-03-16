void StartTransaction ( Archive * AHX ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 ExecuteSqlCommand ( AH , "BEGIN" , "could not start database transaction" ) ;
 }