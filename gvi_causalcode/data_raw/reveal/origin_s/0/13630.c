static int verify_merge_base ( unsigned char * head_sha1 , struct ref * remote ) {
 struct commit * head = lookup_commit_or_die ( head_sha1 , "HEAD" ) ;
 struct commit * branch = lookup_commit_or_die ( remote -> old_oid . hash , remote -> name ) ;
 return in_merge_bases ( branch , head ) ;
 }