const char * keyring_get_resource_name ( KEYRING_HANDLE hd ) {
 if ( ! hd || ! hd -> resource ) return NULL ;
 return hd -> resource -> fname ;
 }