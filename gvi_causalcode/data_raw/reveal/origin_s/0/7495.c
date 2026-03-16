inline GRANT_TABLE * table_hash_search ( const char * host , const char * ip , const char * db , const char * user , const char * tname , bool exact ) {
 return ( GRANT_TABLE * ) name_hash_search ( & column_priv_hash , host , ip , db , user , tname , exact , FALSE ) ;
 }