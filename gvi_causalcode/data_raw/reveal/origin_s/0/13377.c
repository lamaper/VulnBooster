static void StrictNamesCheck ( RestoreOptions * ropt ) {
 const char * missing_name ;
 Assert ( ropt -> strict_names ) ;
 if ( ropt -> schemaNames . head != NULL ) {
 missing_name = simple_string_list_not_touched ( & ropt -> schemaNames ) ;
 if ( missing_name != NULL ) exit_horribly ( modulename , "schema \"%s\" not found\n" , missing_name ) ;
 }
 if ( ropt -> tableNames . head != NULL ) {
 missing_name = simple_string_list_not_touched ( & ropt -> tableNames ) ;
 if ( missing_name != NULL ) exit_horribly ( modulename , "table \"%s\" not found\n" , missing_name ) ;
 }
 if ( ropt -> indexNames . head != NULL ) {
 missing_name = simple_string_list_not_touched ( & ropt -> indexNames ) ;
 if ( missing_name != NULL ) exit_horribly ( modulename , "index \"%s\" not found\n" , missing_name ) ;
 }
 if ( ropt -> functionNames . head != NULL ) {
 missing_name = simple_string_list_not_touched ( & ropt -> functionNames ) ;
 if ( missing_name != NULL ) exit_horribly ( modulename , "function \"%s\" not found\n" , missing_name ) ;
 }
 if ( ropt -> triggerNames . head != NULL ) {
 missing_name = simple_string_list_not_touched ( & ropt -> triggerNames ) ;
 if ( missing_name != NULL ) exit_horribly ( modulename , "trigger \"%s\" not found\n" , missing_name ) ;
 }
 }