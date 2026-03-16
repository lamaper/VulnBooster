static afs_int32 newEntry ( struct rx_call * call , char aname [ ] , afs_int32 flag , afs_int32 oid , afs_int32 * aid , afs_int32 * cid ) {
 afs_int32 code ;
 struct ubik_trans * tt ;
 int admin ;
 char cname [ PR_MAXNAMELEN ] ;
 stolower ( aname ) ;
 code = Initdb ( ) ;
 if ( code ) return code ;
 code = ubik_BeginTrans ( dbase , UBIK_WRITETRANS , & tt ) ;
 if ( code ) return code ;
 code = ubik_SetLock ( tt , 1 , 1 , LOCKWRITE ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = read_DbHeader ( tt ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = WhoIsThisWithName ( call , tt , cid , cname ) ;
 if ( code && code != 2 ) ABORT_WITH ( tt , PRPERM ) ;
 admin = IsAMemberOf ( tt , * cid , SYSADMINID ) ;
 if ( code == 2 ) {
 if ( ! restricted && ( strcmp ( aname , cname ) == 0 ) ) {
 if ( oid != 0 ) ABORT_WITH ( tt , PRPERM ) ;
 admin = 1 ;
 oid = SYSADMINID ;
 * cid = SYSADMINID ;
 }
 }
 if ( ! CreateOK ( tt , * cid , oid , flag , admin ) ) ABORT_WITH ( tt , PRPERM ) ;
 code = CreateEntry ( tt , aname , aid , 0 , flag , oid , * cid ) ;
 if ( code != PRSUCCESS ) ABORT_WITH ( tt , code ) ;
 code = ubik_EndTrans ( tt ) ;
 if ( code ) return code ;
 return PRSUCCESS ;
 }