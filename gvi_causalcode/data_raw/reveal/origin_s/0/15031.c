static const char * add_marker ( cmd_parms * cmd , directory_config * dcfg , const char * p1 , const char * p2 , const char * p3 ) {
 char * my_error_msg = NULL ;
 msre_rule * rule = NULL ;
 extern msc_engine * modsecurity ;
 int p ;


 dcfg -> ruleset = msre_ruleset_create ( modsecurity -> msre , cmd -> pool ) ;
 if ( dcfg -> ruleset == NULL ) return FATAL_ERROR ;
 }
 rule = msre_rule_create ( dcfg -> ruleset , RULE_TYPE_MARKER , cmd -> directive -> filename , cmd -> directive -> line_num , p1 , p2 , p3 , & my_error_msg ) ;
 if ( rule == NULL ) {
 return my_error_msg ;
 }
 rule -> placeholder = RULE_PH_MARKER ;
 for ( p = PHASE_FIRST ;
 p <= PHASE_LAST ;
 p ++ ) {


 return "Internal Error: Failed to add marker to the ruleset." ;
 }
 }
 if ( dcfg -> tmp_rule_placeholders != NULL ) {
 apr_table_unset ( dcfg -> tmp_rule_placeholders , rule -> actionset -> id ) ;
 }
 return NULL ;
 }