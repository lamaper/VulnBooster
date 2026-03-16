static krb5_boolean policy_exists ( const char * name ) {
 kadm5_policy_ent_rec pol ;
 if ( kadm5_get_policy ( handle , ( char * ) name , & pol ) != 0 ) return FALSE ;
 kadm5_free_policy_ent ( handle , & pol ) ;
 return TRUE ;
 }