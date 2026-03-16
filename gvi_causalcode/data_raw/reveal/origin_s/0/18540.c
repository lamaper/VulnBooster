static gboolean logcat_binary_dump ( wtap_dumper * wdh , const struct wtap_pkthdr * phdr , const guint8 * pd , int * err ) {
 if ( phdr -> rec_type != REC_TYPE_PACKET ) {
 * err = WTAP_ERR_REC_TYPE_UNSUPPORTED ;
 return FALSE ;
 }
 if ( ! wtap_dump_file_write ( wdh , pd , phdr -> caplen , err ) ) return FALSE ;
 wdh -> bytes_dumped += phdr -> caplen ;
 return TRUE ;
 }