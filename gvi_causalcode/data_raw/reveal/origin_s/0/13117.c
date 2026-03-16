static const char * add_rule ( cmd_parms * cmd , directory_config * dcfg , int type , const char * p1 , const char * p2 , const char * p3 ) {
 char * my_error_msg = NULL ;
 char * rid = NULL ;
 msre_rule * rule = NULL ;
 extern msc_engine * modsecurity ;
 int offset = 0 ;


 dcfg -> ruleset = msre_ruleset_create ( modsecurity -> msre , cmd -> pool ) ;
 if ( dcfg -> ruleset == NULL ) return FATAL_ERROR ;
 }
 switch ( type ) {

 break ;

 break ;
 }
 if ( rule == NULL ) {
 return my_error_msg ;
 }
 if ( # if defined ( WITH_LUA ) type != RULE_TYPE_LUA && # endif ( dcfg -> tmp_chain_starter == NULL ) ) if ( rule -> actionset == NULL ) return "ModSecurity: Rules must have at least id action" ;
 if ( rule -> actionset != NULL && ( dcfg -> tmp_chain_starter == NULL ) ) {
 if ( rule -> actionset -> id == NOT_SET_P # if defined ( WITH_LUA ) && ( type != RULE_TYPE_LUA ) # endif ) return "ModSecurity: No action id present within the rule" ;

 rid = apr_hash_get ( dcfg -> rule_id_htab , rule -> actionset -> id , APR_HASH_KEY_STRING ) ;
 if ( rid != NULL ) {
 return "ModSecurity: Found another rule with the same id" ;
 }
 else {
 apr_hash_set ( dcfg -> rule_id_htab , apr_pstrdup ( dcfg -> mp , rule -> actionset -> id ) , APR_HASH_KEY_STRING , apr_pstrdup ( dcfg -> mp , "1" ) ) ;
 }
 }
 }
 if ( dcfg -> tmp_default_actionset == NULL ) {
 dcfg -> tmp_default_actionset = msre_actionset_create_default ( modsecurity -> msre ) ;
 if ( dcfg -> tmp_default_actionset == NULL ) return FATAL_ERROR ;
 }
 if ( ( rule -> actionset != NULL ) && ( dcfg -> tmp_chain_starter != NULL ) ) {
 if ( rule -> actionset -> intercept_action != NOT_SET ) {
 return apr_psprintf ( cmd -> pool , "ModSecurity: Disruptive actions can only " "be specified by chain starter rules." ) ;
 }
 if ( rule -> actionset -> skip_after != NOT_SET_P ) {
 return apr_psprintf ( cmd -> pool , "ModSecurity: SkipAfter actions can only " "be specified by chain starter rules." ) ;
 }
 if ( rule -> actionset -> phase != NOT_SET ) {
 return apr_psprintf ( cmd -> pool , "ModSecurity: Execution phases can only be " "specified by chain starter rules." ) ;
 }
 if ( ( rule -> actionset -> id != NOT_SET_P ) || ( rule -> actionset -> rev != NOT_SET_P ) || ( rule -> actionset -> msg != NOT_SET_P ) || ( rule -> actionset -> severity != NOT_SET ) || ( rule -> actionset -> version != NOT_SET_P ) || ( rule -> actionset -> accuracy != NOT_SET ) || ( rule -> actionset -> maturity != NOT_SET ) || ( rule -> actionset -> logdata != NOT_SET_P ) ) {
 return apr_psprintf ( cmd -> pool , "ModSecurity: Metadata actions (id, rev, msg, tag, severity, ver, accuracy, maturity, logdata) " " can only be specified by chain starter rules." ) ;
 }
 if ( rule -> actionset -> skip_count != NOT_SET ) {
 return apr_psprintf ( cmd -> pool , "ModSecurity: The skip action can only be used " " by chain starter rules. " ) ;
 }
 }
 rule -> actionset = msre_actionset_merge ( modsecurity -> msre , dcfg -> tmp_default_actionset , rule -> actionset , 1 ) ;
 rule -> actionset -> parent_intercept_action_rec = dcfg -> tmp_default_actionset -> intercept_action_rec ;
 rule -> actionset -> parent_intercept_action = dcfg -> tmp_default_actionset -> intercept_action ;
 if ( ( rule -> actionset != NULL ) && ( rule -> actionset -> phase == PHASE_LOGGING ) && ( rule -> actionset -> intercept_action != ACTION_ALLOW ) && ( rule -> actionset -> intercept_action != ACTION_ALLOW_REQUEST ) && ( rule -> actionset -> intercept_action != ACTION_NONE ) ) {
 return apr_psprintf ( cmd -> pool , "ModSecurity: Disruptive actions " "cannot be specified in the logging phase." ) ;
 }
 if ( dcfg -> tmp_chain_starter != NULL ) {
 rule -> chain_starter = dcfg -> tmp_chain_starter ;
 rule -> actionset -> phase = rule -> chain_starter -> actionset -> phase ;
 }
 if ( rule -> actionset -> is_chained != 1 ) {
 dcfg -> tmp_chain_starter = NULL ;
 }
 else {
 if ( dcfg -> tmp_chain_starter == NULL ) {
 dcfg -> tmp_chain_starter = rule ;
 }
 }
 if ( ( rule -> op_name != NULL ) && ( strcasecmp ( rule -> op_name , "inspectFile" ) == 0 ) ) {
 dcfg -> upload_validates_files = 1 ;
 }
 if ( dcfg -> tmp_rule_placeholders == NULL ) {
 dcfg -> tmp_rule_placeholders = apr_table_make ( cmd -> pool , 10 ) ;
 if ( dcfg -> tmp_rule_placeholders == NULL ) return FATAL_ERROR ;
 }
 if ( rule -> actionset -> skip_after != NOT_SET_P ) {
 char * tmp_id = apr_pstrdup ( cmd -> pool , rule -> actionset -> skip_after ) ;
 apr_table_setn ( dcfg -> tmp_rule_placeholders , tmp_id , tmp_id ) ;




 return "Internal Error: Failed to add rule to the ruleset." ;
 }
 if ( ( rule -> actionset -> id != NULL ) && apr_table_get ( dcfg -> tmp_rule_placeholders , rule -> actionset -> id ) ) {
 msre_rule * phrule = apr_palloc ( rule -> ruleset -> mp , sizeof ( msre_rule ) ) ;
 if ( phrule == NULL ) {
 return FATAL_ERROR ;
 }


 phrule -> placeholder = RULE_PH_SKIPAFTER ;
 if ( msre_ruleset_rule_add ( dcfg -> ruleset , phrule , phrule -> actionset -> phase ) < 0 ) {
 return "Internal Error: Failed to add placeholder to the ruleset." ;
 }
 apr_table_unset ( dcfg -> tmp_rule_placeholders , rule -> actionset -> id ) ;
 }
 rule -> unparsed = msre_rule_generate_unparsed ( dcfg -> ruleset -> mp , rule , NULL , NULL , NULL ) ;
 return NULL ;
 }