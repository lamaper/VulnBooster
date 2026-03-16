static ParallelSlot * GetIdleSlot ( ParallelSlot slots [ ] , int numslots , const char * progname ) {
 int i ;
 int firstFree = - 1 ;
 fd_set slotset ;
 pgsocket maxFd ;
 for ( i = 0 ;
 i < numslots ;
 i ++ ) if ( ( slots + i ) -> isFree ) return slots + i ;
 FD_ZERO ( & slotset ) ;
 maxFd = slots -> sock ;
 for ( i = 0 ;
 i < numslots ;
 i ++ ) {
 FD_SET ( ( slots + i ) -> sock , & slotset ) ;
 if ( ( slots + i ) -> sock > maxFd ) maxFd = ( slots + i ) -> sock ;
 }
 for ( firstFree = - 1 ;
 firstFree < 0 ;
 ) {
 bool aborting ;
 SetCancelConn ( slots -> connection ) ;
 i = select_loop ( maxFd , & slotset , & aborting ) ;
 ResetCancelConn ( ) ;
 if ( aborting ) {
 GetQueryResult ( slots -> connection , progname ) ;
 return NULL ;
 }
 Assert ( i != 0 ) ;
 for ( i = 0 ;
 i < numslots ;
 i ++ ) {
 if ( ! FD_ISSET ( ( slots + i ) -> sock , & slotset ) ) continue ;
 PQconsumeInput ( ( slots + i ) -> connection ) ;
 if ( PQisBusy ( ( slots + i ) -> connection ) ) continue ;
 ( slots + i ) -> isFree = true ;
 if ( ! GetQueryResult ( ( slots + i ) -> connection , progname ) ) return NULL ;
 if ( firstFree < 0 ) firstFree = i ;
 }
 }
 return slots + firstFree ;
 }