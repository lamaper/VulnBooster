static void _becomeOwner ( ArchiveHandle * AH , TocEntry * te ) {
 RestoreOptions * ropt = AH -> public . ropt ;
 if ( ropt && ( ropt -> noOwner || ! ropt -> use_setsessauth ) ) return ;
 _becomeUser ( AH , te -> owner ) ;
 }