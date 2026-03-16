static void check_locks ( void ) {
 struct remote_lock * lock = repo -> locks ;
 time_t current_time = time ( NULL ) ;
 int time_remaining ;
 while ( lock ) {
 time_remaining = lock -> start_time + lock -> timeout - current_time ;
 if ( ! lock -> refreshing && time_remaining < LOCK_REFRESH ) {
 if ( ! refresh_lock ( lock ) ) {
 fprintf ( stderr , "Unable to refresh lock for %s\n" , lock -> url ) ;
 aborted = 1 ;
 return ;
 }
 }
 lock = lock -> next ;
 }
 }