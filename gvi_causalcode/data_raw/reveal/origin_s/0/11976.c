static void buildShSecLabels ( PGconn * conn , const char * catalog_name , uint32 objectId , PQExpBuffer buffer , const char * target , const char * objname ) {
 PQExpBuffer sql = createPQExpBuffer ( ) ;
 PGresult * res ;
 buildShSecLabelQuery ( conn , catalog_name , objectId , sql ) ;
 res = executeQuery ( conn , sql -> data ) ;
 emitShSecLabels ( conn , res , buffer , target , objname ) ;
 PQclear ( res ) ;
 destroyPQExpBuffer ( sql ) ;
 }