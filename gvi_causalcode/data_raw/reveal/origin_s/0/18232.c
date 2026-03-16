static inline bool auth_principal_needs_rotating_keys ( EntityName & name ) {
 uint32_t ty ( name . get_type ( ) ) ;
 return ( ( ty == CEPH_ENTITY_TYPE_OSD ) || ( ty == CEPH_ENTITY_TYPE_MDS ) || ( ty == CEPH_ENTITY_TYPE_MGR ) ) ;
 }