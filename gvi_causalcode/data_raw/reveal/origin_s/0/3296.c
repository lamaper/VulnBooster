void StartRestoreBlob ( ArchiveHandle * AH , Oid oid , bool drop ) {
 bool old_blob_style = ( AH -> version < K_VERS_1_12 ) ;
 Oid loOid ;
 AH -> blobCount ++ ;
 AH -> lo_buf_used = 0 ;
 ahlog ( AH , 1 , "restoring large object with OID %u\n" , oid ) ;
 if ( old_blob_style && drop ) DropBlobIfExists ( AH , oid ) ;
 if ( AH -> connection ) {
 if ( old_blob_style ) {
 loOid = lo_create ( AH -> connection , oid ) ;
 if ( loOid == 0 || loOid != oid ) exit_horribly ( modulename , "could not create large object %u: %s" , oid , PQerrorMessage ( AH -> connection ) ) ;
 }
 AH -> loFd = lo_open ( AH -> connection , oid , INV_WRITE ) ;
 if ( AH -> loFd == - 1 ) exit_horribly ( modulename , "could not open large object %u: %s" , oid , PQerrorMessage ( AH -> connection ) ) ;
 }
 else {
 if ( old_blob_style ) ahprintf ( AH , "SELECT pg_catalog.lo_open(pg_catalog.lo_create('%u'), %d);
\n" , oid , INV_WRITE ) ;
 else ahprintf ( AH , "SELECT pg_catalog.lo_open('%u', %d);
\n" , oid , INV_WRITE ) ;
 }
 AH -> writingBlob = 1 ;
 }