static afs_int32 changeEntry ( struct rx_call * call , afs_int32 aid , char * name , afs_int32 oid , afs_int32 newid , afs_int32 * cid ) {
 afs_int32 code ;
 struct ubik_trans * tt ;
 afs_int32 pos ;
 if ( ! name ) return PRPERM ;
 stolower ( name ) ;
 code = Initdb ( ) ;
 if ( code ) return code ;
 if ( aid == ANYUSERID || aid == AUTHUSERID || aid == ANONYMOUSID || aid == SYSADMINID ) return PRPERM ;
 if ( code != PRSUCCESS ) return code ;
 code = ubik_BeginTrans ( dbase , UBIK_WRITETRANS , & tt ) ;
 if ( code ) return code ;
 code = ubik_SetLock ( tt , 1 , 1 , LOCKWRITE ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = read_DbHeader ( tt ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = WhoIsThis ( call , tt , cid ) ;
 if ( code ) ABORT_WITH ( tt , PRPERM ) ;
 pos = FindByID ( tt , aid ) ;
 if ( ! pos ) ABORT_WITH ( tt , PRNOENT ) ;
 code = ChangeEntry ( tt , aid , * cid , name , oid , newid ) ;
 if ( code != PRSUCCESS ) ABORT_WITH ( tt , code ) ;
 code = ubik_EndTrans ( tt ) ;
 return code ;
 }