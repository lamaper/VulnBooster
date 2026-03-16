static inline struct link_map * find_needed ( const char * name ) {
 struct r_scope_elem * scope = & GL ( dl_ns ) [ LM_ID_BASE ] . _ns_loaded -> l_searchlist ;
 unsigned int n = scope -> r_nlist ;
 while ( n -- > 0 ) if ( _dl_name_match_p ( name , scope -> r_list [ n ] ) ) return scope -> r_list [ n ] ;
 return NULL ;
 }