static teReqs _tocEntryRequired ( TocEntry * te , teSection curSection , RestoreOptions * ropt ) {
 teReqs res = REQ_SCHEMA | REQ_DATA ;
 if ( strcmp ( te -> desc , "ENCODING" ) == 0 || strcmp ( te -> desc , "STDSTRINGS" ) == 0 ) return REQ_SPECIAL ;
 if ( ropt -> aclsSkip && _tocEntryIsACL ( te ) ) return 0 ;
 if ( ropt -> no_security_labels && strcmp ( te -> desc , "SECURITY LABEL" ) == 0 ) return 0 ;
 switch ( curSection ) {
 case SECTION_PRE_DATA : if ( ! ( ropt -> dumpSections & DUMP_PRE_DATA ) ) return 0 ;
 break ;
 case SECTION_DATA : if ( ! ( ropt -> dumpSections & DUMP_DATA ) ) return 0 ;
 break ;
 case SECTION_POST_DATA : if ( ! ( ropt -> dumpSections & DUMP_POST_DATA ) ) return 0 ;
 break ;
 default : return 0 ;
 }
 if ( ropt -> schemaNames . head != NULL ) {
 if ( ! te -> namespace ) return 0 ;
 if ( ! ( simple_string_list_member ( & ropt -> schemaNames , te -> namespace ) ) ) return 0 ;
 }
 if ( ropt -> selTypes ) {
 if ( strcmp ( te -> desc , "TABLE" ) == 0 || strcmp ( te -> desc , "TABLE DATA" ) == 0 || strcmp ( te -> desc , "VIEW" ) == 0 || strcmp ( te -> desc , "FOREIGN TABLE" ) == 0 || strcmp ( te -> desc , "MATERIALIZED VIEW" ) == 0 || strcmp ( te -> desc , "MATERIALIZED VIEW DATA" ) == 0 || strcmp ( te -> desc , "SEQUENCE" ) == 0 || strcmp ( te -> desc , "SEQUENCE SET" ) == 0 ) {
 if ( ! ropt -> selTable ) return 0 ;
 if ( ropt -> tableNames . head != NULL && ( ! ( simple_string_list_member ( & ropt -> tableNames , te -> tag ) ) ) ) return 0 ;
 }
 else if ( strcmp ( te -> desc , "INDEX" ) == 0 ) {
 if ( ! ropt -> selIndex ) return 0 ;
 if ( ropt -> indexNames . head != NULL && ( ! ( simple_string_list_member ( & ropt -> indexNames , te -> tag ) ) ) ) return 0 ;
 }
 else if ( strcmp ( te -> desc , "FUNCTION" ) == 0 ) {
 if ( ! ropt -> selFunction ) return 0 ;
 if ( ropt -> functionNames . head != NULL && ( ! ( simple_string_list_member ( & ropt -> functionNames , te -> tag ) ) ) ) return 0 ;
 }
 else if ( strcmp ( te -> desc , "TRIGGER" ) == 0 ) {
 if ( ! ropt -> selTrigger ) return 0 ;
 if ( ropt -> triggerNames . head != NULL && ( ! ( simple_string_list_member ( & ropt -> triggerNames , te -> tag ) ) ) ) return 0 ;
 }
 else return 0 ;
 }
 if ( ! te -> hadDumper ) {
 if ( strcmp ( te -> desc , "SEQUENCE SET" ) == 0 || strcmp ( te -> desc , "BLOB" ) == 0 || ( strcmp ( te -> desc , "ACL" ) == 0 && strncmp ( te -> tag , "LARGE OBJECT " , 13 ) == 0 ) || ( strcmp ( te -> desc , "COMMENT" ) == 0 && strncmp ( te -> tag , "LARGE OBJECT " , 13 ) == 0 ) || ( strcmp ( te -> desc , "SECURITY LABEL" ) == 0 && strncmp ( te -> tag , "LARGE OBJECT " , 13 ) == 0 ) ) res = res & REQ_DATA ;
 else res = res & ~ REQ_DATA ;
 }
 if ( ( strcmp ( te -> desc , "<Init>" ) == 0 ) && ( strcmp ( te -> tag , "Max OID" ) == 0 ) ) return 0 ;
 if ( ropt -> schemaOnly ) res = res & REQ_SCHEMA ;
 if ( ropt -> dataOnly ) res = res & REQ_DATA ;
 if ( ! te -> defn || strlen ( te -> defn ) == 0 ) res = res & ~ REQ_SCHEMA ;
 if ( ropt -> idWanted && ! ropt -> idWanted [ te -> dumpId - 1 ] ) return 0 ;
 return res ;
 }