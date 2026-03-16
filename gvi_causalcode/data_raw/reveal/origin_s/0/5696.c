inline GRANT_COLUMN * column_hash_search ( GRANT_TABLE * t , const char * cname , uint length ) {
 return ( GRANT_COLUMN * ) hash_search ( & t -> hash_columns , ( uchar * ) cname , length ) ;
 }