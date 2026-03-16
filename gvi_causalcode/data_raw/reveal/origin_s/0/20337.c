static void _enableTriggersIfNecessary ( ArchiveHandle * AH , TocEntry * te ) {
 RestoreOptions * ropt = AH -> public . ropt ;
 if ( ! ropt -> dataOnly || ! ropt -> disable_triggers ) return ;
 ahlog ( AH , 1 , "enabling triggers for %s\n" , te -> tag ) ;
 _becomeUser ( AH , ropt -> superuser ) ;
 _selectOutputSchema ( AH , te -> namespace ) ;
 ahprintf ( AH , "ALTER TABLE %s ENABLE TRIGGER ALL;
\n\n" , fmtId ( te -> tag ) ) ;
 }