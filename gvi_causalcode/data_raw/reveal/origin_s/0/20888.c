void modsecurity_child_init ( msc_engine * msce ) {
 xmlInitParser ( ) ;
 if ( msce -> auditlog_lock != NULL ) {
 apr_status_t rc = apr_global_mutex_child_init ( & msce -> auditlog_lock , NULL , msce -> mp ) ;
 if ( rc != APR_SUCCESS ) {
 }
 }
 if ( msce -> geo_lock != NULL ) {
 apr_status_t rc = apr_global_mutex_child_init ( & msce -> geo_lock , NULL , msce -> mp ) ;
 if ( rc != APR_SUCCESS ) {
 }
 }
 }