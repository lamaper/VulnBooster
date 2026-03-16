static gboolean ngsniffer_dump_finish ( wtap_dumper * wdh , int * err ) {
 char buf [ 6 ] = {
 REC_EOF , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 }
 ;
 if ( ! wtap_dump_file_write ( wdh , buf , 6 , err ) ) return FALSE ;
 return TRUE ;
 }