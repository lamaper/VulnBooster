void StartRestoreBlobs ( ArchiveHandle * AH ) {
 RestoreOptions * ropt = AH -> public . ropt ;
 if ( ! ropt -> single_txn ) {
 if ( AH -> connection ) StartTransaction ( & AH -> public ) ;
 else ahprintf ( AH , "BEGIN;
\n\n" ) ;
 }
 AH -> blobCount = 0 ;
 }