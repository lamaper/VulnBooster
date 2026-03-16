static afs_int32 Delete ( struct rx_call * call , afs_int32 aid , afs_int32 * cid ) {
 afs_int32 code ;
 struct ubik_trans * tt ;
 struct prentry tentry ;
 afs_int32 loc , nptr ;
 int count ;
 code = Initdb ( ) ;
 if ( code ) return code ;
 if ( code != PRSUCCESS ) return code ;
 if ( aid == SYSADMINID || aid == ANYUSERID || aid == AUTHUSERID || aid == ANONYMOUSID ) return PRPERM ;
 code = ubik_BeginTrans ( dbase , UBIK_WRITETRANS , & tt ) ;
 if ( code ) return code ;
 code = ubik_SetLock ( tt , 1 , 1 , LOCKWRITE ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = read_DbHeader ( tt ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = WhoIsThis ( call , tt , cid ) ;
 if ( code ) ABORT_WITH ( tt , PRPERM ) ;
 loc = FindByID ( tt , aid ) ;
 if ( loc == 0 ) ABORT_WITH ( tt , PRNOENT ) ;
 code = pr_ReadEntry ( tt , 0 , loc , & tentry ) ;
 if ( code ) ABORT_WITH ( tt , PRDBFAIL ) ;
 if ( tentry . owner != * cid && ! IsAMemberOf ( tt , * cid , SYSADMINID ) && ! IsAMemberOf ( tt , * cid , tentry . owner ) && ! pr_noAuth ) ABORT_WITH ( tt , PRPERM ) ;
 nptr = tentry . next ;
 while ( nptr != 0 ) {
 struct contentry centry ;
 int i ;
 code = pr_ReadCoEntry ( tt , 0 , nptr , & centry ) ;
 if ( code != 0 ) ABORT_WITH ( tt , PRDBFAIL ) ;
 for ( i = 0 ;
 i < COSIZE ;
 i ++ ) {
 if ( centry . entries [ i ] == PRBADID ) continue ;
 if ( centry . entries [ i ] == 0 ) break ;

 else # endif code = RemoveFromEntry ( tt , aid , centry . entries [ i ] ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 tentry . count -- ;


 tentry . next = centry . next ;
 code = FreeBlock ( tt , nptr ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = pr_WriteEntry ( tt , 0 , loc , & tentry ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = ubik_EndTrans ( tt ) ;
 if ( code ) return code ;


 if ( code ) return code ;
 code = ubik_SetLock ( tt , 1 , 1 , LOCKWRITE ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 loc = FindByID ( tt , aid ) ;
 if ( loc == 0 ) ABORT_WITH ( tt , PRNOENT ) ;
 code = pr_ReadEntry ( tt , 0 , loc , & tentry ) ;
 if ( code ) ABORT_WITH ( tt , PRDBFAIL ) ;
 nptr = tentry . next ;
 }

 struct prentryg * tentryg = ( struct prentryg * ) & tentry ;
 nptr = tentryg -> nextsg ;
 while ( nptr != 0 ) {
 struct contentry centry ;
 int i ;
 code = pr_ReadCoEntry ( tt , 0 , nptr , & centry ) ;
 if ( code != 0 ) ABORT_WITH ( tt , PRDBFAIL ) ;
 for ( i = 0 ;
 i < COSIZE ;
 i ++ ) {
 if ( centry . entries [ i ] == PRBADID ) continue ;
 if ( centry . entries [ i ] == 0 ) break ;
 code = RemoveFromEntry ( tt , aid , centry . entries [ i ] ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 tentryg -> countsg -- ;


 tentryg -> nextsg = centry . next ;
 code = FreeBlock ( tt , nptr ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = pr_WriteEntry ( tt , 0 , loc , & tentry ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = ubik_EndTrans ( tt ) ;
 if ( code ) return code ;


 if ( code ) return code ;
 code = ubik_SetLock ( tt , 1 , 1 , LOCKWRITE ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 loc = FindByID ( tt , aid ) ;
 if ( loc == 0 ) ABORT_WITH ( tt , PRNOENT ) ;
 code = pr_ReadEntry ( tt , 0 , loc , & tentry ) ;
 if ( code ) ABORT_WITH ( tt , PRDBFAIL ) ;
 nptr = tentryg -> nextsg ;
 }
 }

 nptr = tentry . owned ;
 while ( nptr != 0 ) {
 struct prentry nentry ;
 code = pr_ReadEntry ( tt , 0 , nptr , & nentry ) ;
 if ( code ) ABORT_WITH ( tt , PRDBFAIL ) ;
 nptr = tentry . owned = nentry . nextOwned ;
 if ( nentry . id != tentry . id ) {
 code = AddToOrphan ( tt , nentry . id ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 count ++ ;


 if ( count < 50 ) continue ;
 code = pr_WriteEntry ( tt , 0 , loc , & tentry ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = ubik_EndTrans ( tt ) ;
 if ( code ) return code ;


 if ( code ) return code ;
 code = ubik_SetLock ( tt , 1 , 1 , LOCKWRITE ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 loc = FindByID ( tt , aid ) ;
 if ( loc == 0 ) ABORT_WITH ( tt , PRNOENT ) ;
 code = pr_ReadEntry ( tt , 0 , loc , & tentry ) ;
 if ( code ) ABORT_WITH ( tt , PRDBFAIL ) ;
 nptr = tentry . owned ;
 }
 code = DeleteEntry ( tt , & tentry , loc ) ;
 if ( code != PRSUCCESS ) ABORT_WITH ( tt , code ) ;
 code = ubik_EndTrans ( tt ) ;
 if ( code ) return code ;
 return PRSUCCESS ;
 }