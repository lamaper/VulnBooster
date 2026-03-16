void DropBlobIfExists ( ArchiveHandle * AH , Oid oid ) {
 if ( AH -> connection == NULL || PQserverVersion ( AH -> connection ) >= 90000 ) {
 ahprintf ( AH , "SELECT pg_catalog.lo_unlink(oid) " "FROM pg_catalog.pg_largeobject_metadata " "WHERE oid = '%u';
\n" , oid ) ;
 }
 else {
 ahprintf ( AH , "SELECT CASE WHEN EXISTS(" "SELECT 1 FROM pg_catalog.pg_largeobject WHERE loid = '%u'" ") THEN pg_catalog.lo_unlink('%u') END;
\n" , oid , oid ) ;
 }
 }