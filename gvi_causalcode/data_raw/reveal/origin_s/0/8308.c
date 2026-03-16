enum nss_status _nss_nis_getaliasent_r ( struct aliasent * alias , char * buffer , size_t buflen , int * errnop ) {
 enum nss_status status ;
 __libc_lock_lock ( lock ) ;
 status = internal_nis_getaliasent_r ( alias , buffer , buflen , errnop ) ;
 __libc_lock_unlock ( lock ) ;
 return status ;
 }