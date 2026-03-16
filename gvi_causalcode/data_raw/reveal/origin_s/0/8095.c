static int ar_parse_common_header ( struct ar * ar , struct archive_entry * entry , const char * h ) {
 uint64_t n ;
 archive_entry_set_mtime ( entry , ( time_t ) ar_atol10 ( h + AR_date_offset , AR_date_size ) , 0L ) ;
 archive_entry_set_uid ( entry , ( uid_t ) ar_atol10 ( h + AR_uid_offset , AR_uid_size ) ) ;
 archive_entry_set_gid ( entry , ( gid_t ) ar_atol10 ( h + AR_gid_offset , AR_gid_size ) ) ;
 archive_entry_set_mode ( entry , ( mode_t ) ar_atol8 ( h + AR_mode_offset , AR_mode_size ) ) ;
 n = ar_atol10 ( h + AR_size_offset , AR_size_size ) ;
 ar -> entry_offset = 0 ;
 ar -> entry_padding = n % 2 ;
 archive_entry_set_size ( entry , n ) ;
 ar -> entry_bytes_remaining = n ;
 return ( ARCHIVE_OK ) ;
 }