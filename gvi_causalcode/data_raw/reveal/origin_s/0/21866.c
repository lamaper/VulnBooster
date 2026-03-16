static void usage ( void ) {
 print_version ( ) ;
 puts ( "By Monty, for your professional use" ) ;
 puts ( "This software comes with NO WARRANTY: see the PUBLIC for details.\n" ) ;
 puts ( "Description, check and repair of MyISAM tables." ) ;
 puts ( "Used without options all tables on the command will be checked for errors" ) ;
 printf ( "Usage: %s [OPTIONS] tables[.MYI]\n" , my_progname_short ) ;
 printf ( "\nGlobal options:\n" ) ;



)" ) ;




 puts ( "Repair options (When using '-r' or '-o'):\n\ -B, --backup Make a backup of the .MYD file as 'filename-time.BAK'.\n\ --correct-checksum Correct checksum information for table.\n\ -D, --data-file-length=# Max length of data file (when recreating data\n\ file when it's full).\n\ -e, --extend-check Try to recover every possible row from the data file\n\ Normally this will also find a lot of garbage rows;
\n\ Don't use this option if you are not totally desperate.\n\ -f, --force Overwrite old temporary files.\n\ -k, --keys-used=# Tell MyISAM to update only some specific keys. # is a\n\ bit mask of which keys to use. This can be used to\n\ get faster inserts.\n\ --max-record-length=#\n\ Skip rows bigger than this if myisamchk can't allocate\n\ memory to hold it.\n\ -r, --recover Can fix almost anything except unique keys that aren't\n\ unique.\n\ -n, --sort-recover Forces recovering with sorting even if the temporary\n\ file would be very big.\n\ -p, --parallel-recover\n\ Uses the same technique as '-r' and '-n', but creates\n\ all the keys in parallel, in different threads.\n\ -o, --safe-recover Uses old recovery method;
 Slower than '-r' but can\n\ handle a couple of cases where '-r' reports that it\n\ can't fix the data file.\n\ --character-sets-dir=...\n\ Directory where character sets are.\n\ --set-collation=name\n\ Change the collation used by the index.\n\ -q, --quick Faster repair by not modifying the data file.\n\ One can give a second '-q' to force myisamchk to\n\ modify the original datafile in case of duplicate keys.\n\ NOTE: Tables where the data file is currupted can't be\n\ fixed with this option.\n\ -u, --unpack Unpack file packed with myisampack.\n\ " ) ;
 puts ( "Other actions:\n\ -a, --analyze Analyze distribution of keys. Will make some joins in\n\ MySQL faster. You can check the calculated distribution\n\ by using '--description --verbose table_name'.\n\ --stats_method=name Specifies how index statistics collection code should\n\ treat NULLs. Possible values of name are \"nulls_unequal\"\n\ (default for 4.1/5.0), \"nulls_equal\" (emulate 4.0), and \n\ \"nulls_ignored\".\n\ -d, --description Prints some information about table.\n\ -A, --set-auto-increment[=value]\n\ Force auto_increment to start at this or higher value\n\ If no value is given, then sets the next auto_increment\n\ value to the highest used value for the auto key + 1.\n\ -S, --sort-index Sort index blocks. This speeds up 'read-next' in\n\ applications.\n\ -R, --sort-records=#\n\ Sort records according to an index. This makes your\n\ data much more localized and may speed up things\n\ (It may be VERY slow to do a sort the first time!).\n\ -b, --block-search=#\n\ Find a record, a block at given offset belongs to." ) ;
 print_defaults ( "my" , load_default_groups ) ;
 my_print_variables ( my_long_options ) ;
 }