static gboolean k12_dump_finish ( wtap_dumper * wdh , int * err ) {
 k12_dump_t * k12 = ( k12_dump_t * ) wdh -> priv ;
 union {
 guint8 b [ sizeof ( guint32 ) ] ;
 guint32 u ;
 }
 d ;
 if ( ! wtap_dump_file_write ( wdh , k12_eof , 2 , err ) ) return FALSE ;
 k12 -> file_len += 2 ;
 if ( wtap_dump_file_seek ( wdh , K12_FILE_HDR_FILE_SIZE , SEEK_SET , err ) == - 1 ) return FALSE ;
 d . u = g_htonl ( k12 -> file_len ) ;
 if ( ! wtap_dump_file_write ( wdh , d . b , 4 , err ) ) return FALSE ;
 if ( wtap_dump_file_seek ( wdh , K12_FILE_HDR_PAGE_SIZE , SEEK_SET , err ) == - 1 ) return FALSE ;
 d . u = g_htonl ( 8192 ) ;
 if ( ! wtap_dump_file_write ( wdh , d . b , 4 , err ) ) return FALSE ;
 if ( wtap_dump_file_seek ( wdh , K12_FILE_HDR_RECORD_COUNT_1 , SEEK_SET , err ) == - 1 ) return FALSE ;
 d . u = g_htonl ( k12 -> num_of_records ) ;
 if ( ! wtap_dump_file_write ( wdh , d . b , 4 , err ) ) return FALSE ;
 if ( wtap_dump_file_seek ( wdh , K12_FILE_HDR_RECORD_COUNT_2 , SEEK_SET , err ) == - 1 ) return FALSE ;
 d . u = g_htonl ( k12 -> num_of_records ) ;
 if ( ! wtap_dump_file_write ( wdh , d . b , 4 , err ) ) return FALSE ;
 return TRUE ;
 }