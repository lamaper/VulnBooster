static int virLogSetDefaultOutputToFile ( const char * filename , bool privileged ) {
 int ret = - 1 ;
 char * logdir = NULL ;
 mode_t old_umask ;
 if ( privileged ) {
 if ( virAsprintf ( & virLogDefaultOutput , "%d:file:%s/log/libvirt/%s" , virLogDefaultPriority , LOCALSTATEDIR , filename ) < 0 ) goto cleanup ;
 }
 else {
 if ( ! ( logdir = virGetUserCacheDirectory ( ) ) ) goto cleanup ;
 old_umask = umask ( 077 ) ;
 if ( virFileMakePath ( logdir ) < 0 ) {
 umask ( old_umask ) ;
 goto cleanup ;
 }
 umask ( old_umask ) ;
 if ( virAsprintf ( & virLogDefaultOutput , "%d:file:%s/%s" , virLogDefaultPriority , logdir , filename ) < 0 ) goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( logdir ) ;
 return ret ;
 }