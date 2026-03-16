static afs_int32 removeFromGroup ( struct rx_call * call , afs_int32 aid , afs_int32 gid , afs_int32 * cid ) {
 afs_int32 code ;
 struct ubik_trans * tt ;
 afs_int32 tempu ;
 afs_int32 tempg ;
 struct prentry uentry ;
 struct prentry gentry ;
 code = Initdb ( ) ;
 if ( code != PRSUCCESS ) return code ;
 code = ubik_BeginTrans ( dbase , UBIK_WRITETRANS , & tt ) ;
 if ( code ) return code ;
 code = ubik_SetLock ( tt , 1 , 1 , LOCKWRITE ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = read_DbHeader ( tt ) ;
 if ( code ) ABORT_WITH ( tt , code ) ;
 code = WhoIsThis ( call , tt , cid ) ;
 if ( code ) ABORT_WITH ( tt , PRPERM ) ;
 tempu = FindByID ( tt , aid ) ;
 if ( ! tempu ) ABORT_WITH ( tt , PRNOENT ) ;
 tempg = FindByID ( tt , gid ) ;
 if ( ! tempg ) ABORT_WITH ( tt , PRNOENT ) ;
 memset ( & uentry , 0 , sizeof ( uentry ) ) ;
 memset ( & gentry , 0 , sizeof ( gentry ) ) ;
 code = pr_ReadEntry ( tt , 0 , tempu , & uentry ) ;
 if ( code != 0 ) ABORT_WITH ( tt , code ) ;
 code = pr_ReadEntry ( tt , 0 , tempg , & gentry ) ;
 if ( code != 0 ) ABORT_WITH ( tt , code ) ;
 if ( ! ( gentry . flags & PRGRP ) ) ABORT_WITH ( tt , PRNOTGROUP ) ;


 code = RemoveFromEntry ( tt , aid , gid ) ;
 if ( code != PRSUCCESS ) ABORT_WITH ( tt , code ) ;



 code = ubik_EndTrans ( tt ) ;
 if ( code ) return code ;
 return PRSUCCESS ;
 }