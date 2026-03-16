DumpOptions * dumpOptionsFromRestoreOptions ( RestoreOptions * ropt ) {
 DumpOptions * dopt = NewDumpOptions ( ) ;
 dopt -> outputClean = ropt -> dropSchema ;
 dopt -> dataOnly = ropt -> dataOnly ;
 dopt -> schemaOnly = ropt -> schemaOnly ;
 dopt -> if_exists = ropt -> if_exists ;
 dopt -> column_inserts = ropt -> column_inserts ;
 dopt -> dumpSections = ropt -> dumpSections ;
 dopt -> aclsSkip = ropt -> aclsSkip ;
 dopt -> outputSuperuser = ropt -> superuser ;
 dopt -> outputCreateDB = ropt -> createDB ;
 dopt -> outputNoOwner = ropt -> noOwner ;
 dopt -> outputNoTablespaces = ropt -> noTablespace ;
 dopt -> disable_triggers = ropt -> disable_triggers ;
 dopt -> use_setsessauth = ropt -> use_setsessauth ;
 dopt -> disable_dollar_quoting = ropt -> disable_dollar_quoting ;
 dopt -> dump_inserts = ropt -> dump_inserts ;
 dopt -> no_security_labels = ropt -> no_security_labels ;
 dopt -> lockWaitTimeout = ropt -> lockWaitTimeout ;
 dopt -> include_everything = ropt -> include_everything ;
 dopt -> enable_row_security = ropt -> enable_row_security ;
 return dopt ;
 }