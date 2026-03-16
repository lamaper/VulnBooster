static char * xml_entities ( const char * s ) {
 struct strbuf buf = STRBUF_INIT ;
 strbuf_addstr_xml_quoted ( & buf , s ) ;
 return strbuf_detach ( & buf , NULL ) ;
 }