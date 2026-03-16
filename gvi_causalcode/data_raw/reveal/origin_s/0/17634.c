int virLogParseDefaultPriority ( const char * priority ) {
 if ( STREQ ( priority , "1" ) || STREQ ( priority , "debug" ) ) return VIR_LOG_DEBUG ;
 else if ( STREQ ( priority , "2" ) || STREQ ( priority , "info" ) ) return VIR_LOG_INFO ;
 else if ( STREQ ( priority , "3" ) || STREQ ( priority , "warning" ) ) return VIR_LOG_WARN ;
 else if ( STREQ ( priority , "4" ) || STREQ ( priority , "error" ) ) return VIR_LOG_ERROR ;
 return - 1 ;
 }