static int qemuMonitorJSONHasError ( virJSONValuePtr reply , const char * klass ) {
 virJSONValuePtr error ;
 const char * thisklass ;
 if ( ! virJSONValueObjectHasKey ( reply , "error" ) ) return 0 ;
 error = virJSONValueObjectGet ( reply , "error" ) ;
 if ( ! error ) return 0 ;
 if ( ! virJSONValueObjectHasKey ( error , "class" ) ) return 0 ;
 thisklass = virJSONValueObjectGetString ( error , "class" ) ;
 if ( ! thisklass ) return 0 ;
 return STREQ ( klass , thisklass ) ;
 }