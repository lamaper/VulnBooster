void SetArchiveOptions ( Archive * AH , DumpOptions * dopt , RestoreOptions * ropt ) {
 if ( dopt == NULL && ropt != NULL ) dopt = dumpOptionsFromRestoreOptions ( ropt ) ;
 AH -> dopt = dopt ;
 AH -> ropt = ropt ;
 }