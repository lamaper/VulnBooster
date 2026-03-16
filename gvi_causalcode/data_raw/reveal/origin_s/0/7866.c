int HandleIoctl ( struct vcache * avc , afs_int32 acom , struct afs_ioctl * adata ) {
 afs_int32 code ;
 code = 0 ;
 AFS_STATCNT ( HandleIoctl ) ;
 switch ( acom & 0xff ) {
 case 1 : avc -> f . states |= CSafeStore ;
 avc -> asynchrony = 0 ;
 break ;
 case 3 : {
 struct cell * tcell ;
 afs_int32 i ;
 tcell = afs_GetCell ( avc -> f . fid . Cell , READ_LOCK ) ;
 if ( tcell ) {
 i = strlen ( tcell -> cellName ) + 1 ;
 if ( i > adata -> out_size ) {
 if ( adata -> out_size != 0 ) code = EFAULT ;
 }
 else {
 AFS_COPYOUT ( tcell -> cellName , adata -> out , i , code ) ;
 }
 afs_PutCell ( tcell , READ_LOCK ) ;
 }
 else code = ENOTTY ;
 }
 break ;
 case 49 : if ( adata -> out_size < sizeof ( struct cm_initparams ) ) {
 code = EFAULT ;
 }
 else {
 AFS_COPYOUT ( & cm_initParams , adata -> out , sizeof ( struct cm_initparams ) , code ) ;
 }
 break ;
 default : code = EINVAL ;


 }
 return code ;
 }