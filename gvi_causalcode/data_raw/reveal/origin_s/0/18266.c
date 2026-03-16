gboolean k12_dump_open ( wtap_dumper * wdh , int * err ) {
 k12_dump_t * k12 ;
 if ( ! wtap_dump_file_write ( wdh , k12_file_magic , 8 , err ) ) {
 return FALSE ;
 }
 if ( wtap_dump_file_seek ( wdh , K12_FILE_HDR_LEN , SEEK_SET , err ) == - 1 ) return FALSE ;
 wdh -> subtype_write = k12_dump ;
 wdh -> subtype_finish = k12_dump_finish ;
 k12 = ( k12_dump_t * ) g_malloc ( sizeof ( k12_dump_t ) ) ;
 wdh -> priv = ( void * ) k12 ;
 k12 -> file_len = K12_FILE_HDR_LEN ;
 k12 -> num_of_records = 0 ;
 k12 -> file_offset = K12_FILE_HDR_LEN ;
 return TRUE ;
 }