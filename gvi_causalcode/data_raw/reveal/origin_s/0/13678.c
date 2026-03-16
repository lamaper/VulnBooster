inline void umtx_initOnce ( UInitOnce & uio , void ( U_CALLCONV * fp ) ( UErrorCode & ) , UErrorCode & errCode ) {
 if ( U_FAILURE ( errCode ) ) {
 return ;
 }
 if ( umtx_loadAcquire ( uio . fState ) != 2 && umtx_initImplPreInit ( uio ) ) {
 ( * fp ) ( errCode ) ;
 uio . fErrCode = errCode ;
 umtx_initImplPostInit ( uio ) ;
 }
 else {
 if ( U_FAILURE ( uio . fErrCode ) ) {
 errCode = uio . fErrCode ;
 }
 }
 }