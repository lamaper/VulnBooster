int set_file_attrs ( const char * fname , struct file_struct * file , stat_x * sxp , const char * fnamecmp , int flags ) {
 int updated = 0 ;
 stat_x sx2 ;
 int change_uid , change_gid ;
 mode_t new_mode = file -> mode ;
 int inherit ;
 if ( ! sxp ) {
 if ( dry_run ) return 1 ;
 if ( link_stat ( fname , & sx2 . st , 0 ) < 0 ) {
 rsyserr ( FERROR_XFER , errno , "stat %s failed" , full_fname ( fname ) ) ;
 return 0 ;
 }
 init_stat_x ( & sx2 ) ;
 sxp = & sx2 ;
 inherit = ! preserve_perms ;
 }
 else inherit = ! preserve_perms && file -> flags & FLAG_DIR_CREATED ;
 if ( inherit && S_ISDIR ( new_mode ) && sxp -> st . st_mode & S_ISGID ) {
 new_mode |= S_ISGID ;
 }
 if ( daemon_chmod_modes && ! S_ISLNK ( new_mode ) ) new_mode = tweak_mode ( new_mode , daemon_chmod_modes ) ;


 change_gid = gid_ndx && ! ( file -> flags & FLAG_SKIP_GROUP ) && sxp -> st . st_gid != ( gid_t ) F_GROUP ( file ) ;

 ;
 }
 else # endif if ( change_uid || change_gid ) {
 if ( DEBUG_GTE ( OWN , 1 ) ) {
 if ( change_uid ) {
 rprintf ( FINFO , "set uid of %s from %u to %u\n" , fname , ( unsigned ) sxp -> st . st_uid , F_OWNER ( file ) ) ;
 }
 if ( change_gid ) {
 rprintf ( FINFO , "set gid of %s from %u to %u\n" , fname , ( unsigned ) sxp -> st . st_gid , F_GROUP ( file ) ) ;
 }
 }
 if ( am_root >= 0 ) {
 uid_t uid = change_uid ? ( uid_t ) F_OWNER ( file ) : sxp -> st . st_uid ;
 gid_t gid = change_gid ? ( gid_t ) F_GROUP ( file ) : sxp -> st . st_gid ;
 if ( do_lchown ( fname , uid , gid ) != 0 ) {
 rsyserr ( FERROR_XFER , errno , "%s %s failed" , change_uid ? "chown" : "chgrp" , full_fname ( fname ) ) ;
 goto cleanup ;
 }
 if ( uid == ( uid_t ) - 1 && sxp -> st . st_uid != ( uid_t ) - 1 ) rprintf ( FERROR_XFER , "uid 4294967295 (-1) is impossible to set on %s\n" , full_fname ( fname ) ) ;
 if ( gid == ( gid_t ) - 1 && sxp -> st . st_gid != ( gid_t ) - 1 ) rprintf ( FERROR_XFER , "gid 4294967295 (-1) is impossible to set on %s\n" , full_fname ( fname ) ) ;
 if ( sxp -> st . st_mode & ( S_ISUID | S_ISGID ) ) {
 link_stat ( fname , & sxp -> st , keep_dirlinks && S_ISDIR ( sxp -> st . st_mode ) ) ;
 }
 }
 updated = 1 ;
 }

 if ( preserve_xattrs && fnamecmp ) set_xattr ( fname , file , fnamecmp , sxp ) ;

 if ( ! ( flags & ATTRS_SKIP_MTIME ) && ( sxp -> st . st_mtime != file -> modtime # ifdef ST_MTIME_NSEC || ( NSEC_BUMP ( file ) && ( uint32 ) sxp -> st . ST_MTIME_NSEC != F_MOD_NSEC ( file ) ) # endif ) ) {
 int ret = set_modtime ( fname , file -> modtime , F_MOD_NSEC ( file ) , sxp -> st . st_mode ) ;
 if ( ret < 0 ) {
 rsyserr ( FERROR_XFER , errno , "failed to set times on %s" , full_fname ( fname ) ) ;
 goto cleanup ;
 }
 if ( ret == 0 ) updated = 1 ;
 else file -> flags |= FLAG_TIME_FAILED ;
 }

 if ( set_acl ( fname , file , sxp , new_mode ) > 0 ) updated = 1 ;
 }

 int ret = am_root < 0 ? 0 : do_chmod ( fname , new_mode ) ;
 if ( ret < 0 ) {
 rsyserr ( FERROR_XFER , errno , "failed to set permissions on %s" , full_fname ( fname ) ) ;
 goto cleanup ;
 }
 if ( ret == 0 ) updated = 1 ;
 }

 if ( updated ) rprintf ( FCLIENT , "%s\n" , fname ) ;
 else rprintf ( FCLIENT , "%s is uptodate\n" , fname ) ;
 }
 cleanup : if ( sxp == & sx2 ) free_stat_x ( & sx2 ) ;
 return updated ;
 }