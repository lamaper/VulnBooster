static const char * qemuMonitorJSONCommandName ( virJSONValuePtr cmd ) {
 const char * name = virJSONValueObjectGetString ( cmd , "execute" ) ;
 if ( name ) return name ;
 else return "<unknown>" ;
 }