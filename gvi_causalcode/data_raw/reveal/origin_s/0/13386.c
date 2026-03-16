static void CheckMake ( SplinePoint * from , SplinePoint * to ) {
 CheckMakeB ( & from -> me , NULL ) ;
 CheckMakeB ( & from -> nextcp , & from -> me ) ;
 CheckMakeB ( & to -> prevcp , & from -> nextcp ) ;
 CheckMakeB ( & to -> me , & to -> prevcp ) ;
 }