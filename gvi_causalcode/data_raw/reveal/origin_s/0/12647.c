int modsecurity_init ( msc_engine * msce , apr_pool_t * mp ) {
 apr_status_t rc ;
 rc = apr_global_mutex_create ( & msce -> auditlog_lock , NULL , APR_LOCK_DEFAULT , mp ) ;
 if ( rc != APR_SUCCESS ) {
 return - 1 ;
 }



 return - 1 ;
 }

 if ( rc != APR_SUCCESS ) {
 return - 1 ;
 }



 return - 1 ;
 }

 }