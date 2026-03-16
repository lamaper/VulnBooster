static void proto_tree_set_string ( field_info * fi , const char * value ) {
 if ( value ) {
 fvalue_set_string ( & fi -> value , value ) ;
 }
 else {
 fvalue_set_string ( & fi -> value , "[ Null ]" ) ;
 }
 }