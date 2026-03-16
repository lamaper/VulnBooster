gboolean ngsniffer_dump_open ( wtap_dumper * wdh , int * err ) {
 ngsniffer_dump_t * ngsniffer ;
 char buf [ 6 ] = {
 REC_VERS , 0x00 , 0x12 , 0x00 , 0x00 , 0x00 }
 ;
 wdh -> subtype_write = ngsniffer_dump ;
 wdh -> subtype_finish = ngsniffer_dump_finish ;
 ngsniffer = ( ngsniffer_dump_t * ) g_malloc ( sizeof ( ngsniffer_dump_t ) ) ;
 wdh -> priv = ( void * ) ngsniffer ;
 ngsniffer -> first_frame = TRUE ;
 ngsniffer -> start = 0 ;
 if ( ! wtap_dump_file_write ( wdh , ngsniffer_magic , sizeof ngsniffer_magic , err ) ) return FALSE ;
 if ( ! wtap_dump_file_write ( wdh , buf , 6 , err ) ) return FALSE ;
 return TRUE ;
 }