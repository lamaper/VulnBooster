inline GRANT_NAME * routine_hash_search ( const char * host , const char * ip , const char * db , const char * user , const char * tname , bool proc , bool exact ) {
 return ( GRANT_TABLE * ) name_hash_search ( proc ? & proc_priv_hash : & func_priv_hash , host , ip , db , user , tname , exact , TRUE ) ;
 }