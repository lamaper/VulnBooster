gboolean logcat_binary_dump_open ( wtap_dumper * wdh , int * err ) {
 wdh -> subtype_write = logcat_binary_dump ;
 wdh -> subtype_close = NULL ;
 switch ( wdh -> encap ) {
 case WTAP_ENCAP_LOGCAT : wdh -> tsprecision = WTAP_FILE_TSPREC_USEC ;
 break ;
 default : * err = WTAP_ERR_UNSUPPORTED_FILE_TYPE ;
 return FALSE ;
 }
 return TRUE ;
 }