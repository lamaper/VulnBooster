static const char * qemuMonitorJSONStringifyError ( virJSONValuePtr error ) {
 const char * klass = virJSONValueObjectGetString ( error , "class" ) ;
 const char * detail = NULL ;
 if ( klass ) detail = virJSONValueObjectGetString ( error , "desc" ) ;
 if ( ! detail ) detail = "unknown QEMU command error" ;
 return detail ;
 }