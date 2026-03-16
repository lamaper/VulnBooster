static const char * update_rule_action ( cmd_parms * cmd , directory_config * dcfg , const char * p1 , const char * p2 , int offset ) {
 char * my_error_msg = NULL ;
 msre_rule * rule = NULL ;
 msre_actionset * new_actionset = NULL ;
 msre_ruleset * ruleset = dcfg -> ruleset ;
 extern msc_engine * modsecurity ;
 if ( ( ruleset == NULL ) || ( ruleset == NOT_SET_P ) ) {
 return NULL ;
 }


 if ( rule == NULL ) {


 }
 if ( rule -> actionset == NULL ) {
 return apr_psprintf ( cmd -> pool , "ModSecurity: Attempt to update action for rule \"%s\" failed: Rule does not have an actionset." , p1 ) ;
 }
 new_actionset = msre_actionset_create ( modsecurity -> msre , p2 , & my_error_msg ) ;
 if ( new_actionset == NULL ) return FATAL_ERROR ;
 if ( my_error_msg != NULL ) return my_error_msg ;
 if ( ( new_actionset -> id != NOT_SET_P ) && ( rule -> actionset -> id != NULL ) && ( strcmp ( rule -> actionset -> id , new_actionset -> id ) != 0 ) ) {
 return apr_psprintf ( cmd -> pool , "ModSecurity: Rule IDs cannot be updated via SecRuleUpdateActionById." ) ;
 }
 if ( ( new_actionset -> phase != NOT_SET ) && ( rule -> actionset -> phase != new_actionset -> phase ) ) {
 return apr_psprintf ( cmd -> pool , "ModSecurity: Rule phases cannot be updated via SecRuleUpdateActionById." ) ;
 }

 char * actions = msre_actionset_generate_action_string ( ruleset -> mp , rule -> actionset ) ;
 ap_log_perror ( APLOG_MARK , APLOG_STARTUP | APLOG_NOERRNO , 0 , cmd -> pool , "Update rule %pp id=\"%s\" old action: \"%s\"" , rule , ( rule -> actionset -> id == NOT_SET_P ? "(none)" : rule -> actionset -> id ) , actions ) ;
 }

 msre_actionset_set_defaults ( rule -> actionset ) ;
 rule -> unparsed = msre_rule_generate_unparsed ( ruleset -> mp , rule , NULL , NULL , NULL ) ;

 char * actions = msre_actionset_generate_action_string ( ruleset -> mp , rule -> actionset ) ;
 ap_log_perror ( APLOG_MARK , APLOG_STARTUP | APLOG_NOERRNO , 0 , cmd -> pool , "Update rule %pp id=\"%s\" new action: \"%s\"" , rule , ( rule -> actionset -> id == NOT_SET_P ? "(none)" : rule -> actionset -> id ) , actions ) ;
 }

 }