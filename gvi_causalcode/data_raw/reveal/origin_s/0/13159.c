int main ( int argc , char * * argv ) # endif {
 static const char * flags = "0123456789cdefhnqvDFJNORTVs:m:B:C:E:I:L:O:M:P:W:A::S::" ;
 xd3_cmd cmd ;
 main_file ifile ;
 main_file ofile ;
 main_file sfile ;
 main_merge_list merge_order ;
 main_merge * merge ;
 int my_optind ;
 const char * my_optarg ;
 const char * my_optstr ;
 const char * sfilename ;
 int env_argc ;
 char * * env_argv ;
 char * * free_argv ;
 char * free_value ;
 int ret ;

 setvbuf ( stderr , NULL , _IONBF , 0 ) ;

 main_file_init ( & ofile ) ;
 main_file_init ( & sfile ) ;
 main_merge_list_init ( & merge_order ) ;
 reset_defaults ( ) ;
 free_argv = NULL ;
 free_value = NULL ;
 setup_environment ( argc , argv , & env_argc , & env_argv , & free_argv , & free_value ) ;
 cmd = CMD_NONE ;
 sfilename = NULL ;
 my_optind = 1 ;
 argv = env_argv ;
 argc = env_argc ;
 program_name = env_argv [ 0 ] ;
 takearg : my_optarg = NULL ;
 my_optstr = argv [ my_optind ] ;
 if ( my_optstr ) {
 if ( * my_optstr == '-' ) {
 my_optstr += 1 ;
 }
 else if ( cmd == CMD_NONE ) {
 goto nonflag ;
 }
 else {
 my_optstr = NULL ;
 }
 }
 while ( my_optstr ) {
 const char * s ;
 my_optarg = NULL ;
 if ( ( ret = * my_optstr ++ ) == 0 ) {
 my_optind += 1 ;
 goto takearg ;
 }
 s = strchr ( flags , ret ) ;
 if ( s && s [ 1 ] && s [ 1 ] == ':' ) {
 int option = s [ 2 ] && s [ 2 ] == ':' ;
 my_optarg = my_optstr ;
 my_optstr = "" ;
 if ( * my_optarg == 0 ) {
 int have_arg = ( my_optind < ( argc - 1 ) && * argv [ my_optind + 1 ] != '-' ) ;
 if ( ! have_arg ) {
 if ( ! option ) {
 XPR ( NT "-%c: requires an argument\n" , ret ) ;
 ret = EXIT_FAILURE ;
 goto cleanup ;
 }
 my_optarg = NULL ;
 }
 else {
 my_optarg = argv [ ++ my_optind ] ;
 }
 }
 else if ( * my_optarg == '=' ) {
 my_optarg += 1 ;
 if ( option && * my_optarg == 0 ) {
 my_optarg = NULL ;
 }
 }
 }
 switch ( ret ) {
 nonflag : if ( strcmp ( my_optstr , "decode" ) == 0 ) {
 cmd = CMD_DECODE ;
 }
 else if ( strcmp ( my_optstr , "encode" ) == 0 ) {


 return EXIT_FAILURE ;

 else if ( strcmp ( my_optstr , "config" ) == 0 ) {
 cmd = CMD_CONFIG ;
 }

 cmd = CMD_TEST ;
 }

 cmd = CMD_PRINTHDR ;
 }
 else if ( strcmp ( my_optstr , "printhdrs" ) == 0 ) {
 cmd = CMD_PRINTHDRS ;
 }
 else if ( strcmp ( my_optstr , "printdelta" ) == 0 ) {
 cmd = CMD_PRINTDELTA ;
 }
 else if ( strcmp ( my_optstr , "recode" ) == 0 ) {
 cmd = CMD_RECODE ;
 }
 else if ( strcmp ( my_optstr , "merge" ) == 0 ) {
 cmd = CMD_MERGE ;
 }

 cmd = CMD_DEFAULT ;
 my_optstr = NULL ;
 break ;
 }
 else {
 my_optind += 1 ;
 goto takearg ;
 }
 case '0' : case '1' : case '2' : case '3' : case '4' : case '5' : case '6' : case '7' : case '8' : case '9' : option_level = ret - '0' ;
 break ;
 case 'f' : option_force = 1 ;
 break ;
 case 'F' : # if EXTERNAL_COMPRESSION option_force2 = 1 ;

 break ;

 option_quiet = 0 ;
 break ;
 case 'q' : option_quiet = 1 ;
 option_verbose = 0 ;
 break ;
 case 'c' : option_stdout = 1 ;
 break ;
 case 'd' : if ( cmd == CMD_NONE ) {
 cmd = CMD_DECODE ;
 }
 else {
 ret = main_help ( ) ;
 goto exit ;
 }
 break ;
 case 'e' : # if XD3_ENCODER if ( cmd == CMD_NONE ) {
 cmd = CMD_ENCODE ;
 }
 else {
 ret = main_help ( ) ;
 goto exit ;
 }
 break ;

 return EXIT_FAILURE ;

 break ;
 case 'N' : option_no_compress = 1 ;
 break ;
 case 'T' : option_use_altcodetable = 1 ;
 break ;
 case 'C' : option_smatch_config = my_optarg ;
 break ;
 case 'J' : option_no_output = 1 ;
 break ;
 case 'S' : if ( my_optarg == NULL ) {
 option_use_secondary = 1 ;
 option_secondary = "none" ;
 }
 else {
 option_use_secondary = 1 ;
 option_secondary = my_optarg ;
 }
 break ;
 case 'A' : if ( my_optarg == NULL ) {
 option_use_appheader = 0 ;
 }
 else {
 option_appheader = ( uint8_t * ) my_optarg ;
 }
 break ;
 case 'B' : {
 xoff_t bsize ;
 if ( ( ret = main_atoux ( my_optarg , & bsize , XD3_MINSRCWINSZ , XD3_MAXSRCWINSZ , 'B' ) ) ) {
 goto exit ;
 }
 option_srcwinsz = bsize ;
 break ;
 }
 case 'I' : if ( ( ret = main_atou ( my_optarg , & option_iopt_size , 0 , 0 , 'I' ) ) ) {
 goto exit ;
 }
 break ;
 case 'P' : if ( ( ret = main_atou ( my_optarg , & option_sprevsz , 0 , 0 , 'P' ) ) ) {
 goto exit ;
 }
 break ;
 case 'W' : if ( ( ret = main_atou ( my_optarg , & option_winsize , XD3_ALLOCSIZE , XD3_HARDMAXWINSIZE , 'W' ) ) ) {
 goto exit ;
 }
 break ;
 case 'D' : # if EXTERNAL_COMPRESSION == 0 if ( option_verbose > 0 ) {
 XPR ( NT "warning: -D option ignored, " "external compression support was not compiled\n" ) ;
 }


 case 'R' : # if EXTERNAL_COMPRESSION == 0 if ( option_verbose > 0 ) {
 XPR ( NT "warning: -R option ignored, " "external compression support was not compiled\n" ) ;
 }


 case 's' : if ( sfilename != NULL ) {
 XPR ( NT "specify only one source file\n" ) ;
 goto cleanup ;
 }
 sfilename = my_optarg ;
 break ;
 case 'm' : if ( ( merge = ( main_merge * ) main_malloc ( sizeof ( main_merge ) ) ) == NULL ) {
 goto cleanup ;
 }
 main_merge_list_push_back ( & merge_order , merge ) ;
 merge -> filename = my_optarg ;
 break ;
 case 'V' : ret = main_version ( ) ;
 goto exit ;
 default : ret = main_help ( ) ;
 goto exit ;
 }
 }
 option_source_filename = sfilename ;
 if ( cmd == CMD_NONE ) {
 cmd = CMD_DEFAULT ;
 }
 argc -= my_optind ;
 argv += my_optind ;
 if ( argc > 2 ) {
 XPR ( NT "too many filenames: %s ...\n" , argv [ 2 ] ) ;
 goto cleanup ;
 }
 ifile . flags = RD_FIRST | RD_MAININPUT ;
 sfile . flags = RD_FIRST ;
 sfile . filename = option_source_filename ;
 if ( argc > 0 ) {
 ifile . filename = argv [ 0 ] ;
 if ( ( ret = main_file_open ( & ifile , ifile . filename , XO_READ ) ) ) {
 goto cleanup ;
 }
 }
 else {
 XSTDIN_XF ( & ifile ) ;
 }
 if ( argc > 1 ) {
 if ( option_stdout && ! option_quiet ) {
 XPR ( NT "warning: -c option overrides output filename: %s\n" , argv [ 1 ] ) ;
 }
 if ( ! option_stdout ) {
 ofile . filename = argv [ 1 ] ;
 }
 }

 goto cleanup ;
 }

 case CMD_PRINTHDR : case CMD_PRINTHDRS : case CMD_PRINTDELTA : # if XD3_ENCODER case CMD_ENCODE : case CMD_RECODE : case CMD_MERGE : # endif case CMD_DECODE : ret = main_input ( cmd , & ifile , & ofile , & sfile ) ;
 break ;

 ret = xd3_selftest ( ) ;
 break ;

 break ;
 default : ret = main_help ( ) ;
 break ;
 }
 if ( 0 ) {
 cleanup : ret = EXIT_FAILURE ;
 exit : ( void ) 0 ;
 }


 main_file_cleanup ( & ofile ) ;
 main_file_cleanup ( & sfile ) ;
 while ( ! main_merge_list_empty ( & merge_order ) ) {
 merge = main_merge_list_pop_front ( & merge_order ) ;
 main_free ( merge ) ;
 }
 main_free ( free_argv ) ;
 main_free ( free_value ) ;
 main_cleanup ( ) ;
 fflush ( stdout ) ;
 fflush ( stderr ) ;
 return ret ;
 }