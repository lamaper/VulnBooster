gboolean logcat_text_long_dump_open ( wtap_dumper * wdh , int * err _U_ ) {
 struct dumper_t * dumper ;
 dumper = ( struct dumper_t * ) g_malloc ( sizeof ( struct dumper_t ) ) ;
 dumper -> type = DUMP_LONG ;
 wdh -> priv = dumper ;
 wdh -> subtype_write = logcat_dump_text ;
 wdh -> subtype_close = NULL ;
 return TRUE ;
 }