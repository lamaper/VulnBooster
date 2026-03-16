static int RestoringToDB ( ArchiveHandle * AH ) {
 RestoreOptions * ropt = AH -> public . ropt ;
 return ( ropt && ropt -> useDB && AH -> connection ) ;
 }