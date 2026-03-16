static const char * qemuAgentStringifyError ( virJSONValuePtr error ) {
 const char * klass = virJSONValueObjectGetString ( error , "class" ) ;
 const char * detail = virJSONValueObjectGetString ( error , "desc" ) ;
 if ( ! detail ) detail = qemuAgentStringifyErrorClass ( klass ) ;
 return detail ;
 }