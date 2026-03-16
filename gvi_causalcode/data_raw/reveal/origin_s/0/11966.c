static gboolean k12_dump_record ( wtap_dumper * wdh , guint32 len , guint8 * buffer , int * err_p ) {
 k12_dump_t * k12 = ( k12_dump_t * ) wdh -> priv ;
 guint32 junky_offset = ( 8192 - ( ( k12 -> file_offset - K12_FILE_HDR_LEN ) % 8192 ) ) % 8192 ;
 if ( len > junky_offset ) {
 if ( junky_offset ) {
 if ( ! wtap_dump_file_write ( wdh , buffer , junky_offset , err_p ) ) return FALSE ;
 }
 if ( ! wtap_dump_file_write ( wdh , dumpy_junk , K12_FILE_BLOB_LEN , err_p ) ) return FALSE ;
 if ( ! wtap_dump_file_write ( wdh , buffer + junky_offset , len - junky_offset , err_p ) ) return FALSE ;
 k12 -> file_offset += len + K12_FILE_BLOB_LEN ;
 k12 -> file_len += len + K12_FILE_BLOB_LEN ;
 }
 else {
 if ( ! wtap_dump_file_write ( wdh , buffer , len , err_p ) ) return FALSE ;
 k12 -> file_offset += len ;
 k12 -> file_len += len ;
 }
 k12 -> num_of_records ++ ;
 return TRUE ;
 }