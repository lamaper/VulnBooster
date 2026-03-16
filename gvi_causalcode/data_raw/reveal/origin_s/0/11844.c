static void copy_rules_phase ( apr_pool_t * mp , apr_array_header_t * parent_phase_arr , apr_array_header_t * child_phase_arr , apr_array_header_t * exceptions_arr ) {
 rule_exception * * exceptions ;
 msre_rule * * rules ;
 int i , j ;
 int mode = 0 ;
 rules = ( msre_rule * * ) parent_phase_arr -> elts ;
 for ( i = 0 ;
 i < parent_phase_arr -> nelts ;
 i ++ ) {
 msre_rule * rule = ( msre_rule * ) rules [ i ] ;
 int copy = 1 ;
 if ( mode == 0 ) {
 exceptions = ( rule_exception * * ) exceptions_arr -> elts ;
 for ( j = 0 ;
 j < exceptions_arr -> nelts ;
 j ++ ) {
 switch ( exceptions [ j ] -> type ) {
 case RULE_EXCEPTION_REMOVE_ID : if ( ( rule -> actionset != NULL ) && ( rule -> actionset -> id != NULL ) ) {
 int ruleid = atoi ( rule -> actionset -> id ) ;
 if ( rule_id_in_range ( ruleid , exceptions [ j ] -> param ) ) copy -- ;
 }
 break ;
 case RULE_EXCEPTION_REMOVE_MSG : if ( ( rule -> actionset != NULL ) && ( rule -> actionset -> msg != NULL ) ) {
 char * my_error_msg = NULL ;
 int rc = msc_regexec ( exceptions [ j ] -> param_data , rule -> actionset -> msg , strlen ( rule -> actionset -> msg ) , & my_error_msg ) ;
 if ( rc >= 0 ) copy -- ;
 }
 break ;
 case RULE_EXCEPTION_REMOVE_TAG : if ( ( rule -> actionset != NULL ) && ( apr_is_empty_table ( rule -> actionset -> actions ) == 0 ) ) {
 char * my_error_msg = NULL ;
 const apr_array_header_t * tarr = NULL ;
 const apr_table_entry_t * telts = NULL ;
 int c ;
 tarr = apr_table_elts ( rule -> actionset -> actions ) ;
 telts = ( const apr_table_entry_t * ) tarr -> elts ;
 for ( c = 0 ;
 c < tarr -> nelts ;
 c ++ ) {
 msre_action * action = ( msre_action * ) telts [ c ] . val ;
 if ( strcmp ( "tag" , action -> metadata -> name ) == 0 ) {
 int rc = msc_regexec ( exceptions [ j ] -> param_data , action -> param , strlen ( action -> param ) , & my_error_msg ) ;
 if ( rc >= 0 ) copy -- ;
 }
 }
 }
 break ;
 }
 }
 if ( copy > 0 ) {


 if ( rule -> actionset -> is_chained ) mode = 2 ;
 }
 else {
 if ( rule -> actionset -> is_chained ) mode = 1 ;
 }
 }
 else {
 if ( mode == 2 ) {


 }
 if ( ( rule -> actionset == NULL ) || ( rule -> actionset -> is_chained == 0 ) ) mode = 0 ;
 }
 }
 }