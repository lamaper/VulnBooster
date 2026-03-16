static void dl_main ( const ElfW ( Phdr ) * phdr , ElfW ( Word ) phnum , ElfW ( Addr ) * user_entry , ElfW ( auxv_t ) * auxv ) {
 const ElfW ( Phdr ) * ph ;
 enum mode mode ;
 struct link_map * main_map ;
 size_t file_size ;
 char * file ;
 bool has_interp = false ;
 unsigned int i ;
 bool prelinked = false ;
 bool rtld_is_main = false ;

 hp_timing_t stop ;
 hp_timing_t diff ;




 GL ( dl_rtld_unlock_recursive ) = rtld_lock_default_unlock_recursive ;

 process_envvars ( & mode ) ;


 rtld_is_main = true ;
 GL ( dl_rtld_map ) . l_name = rtld_progname ;
 while ( _dl_argc > 1 ) if ( ! strcmp ( _dl_argv [ 1 ] , "--list" ) ) {
 mode = list ;
 GLRO ( dl_lazy ) = - 1 ;
 ++ _dl_skip_args ;
 -- _dl_argc ;
 ++ _dl_argv ;
 }
 else if ( ! strcmp ( _dl_argv [ 1 ] , "--verify" ) ) {
 mode = verify ;
 ++ _dl_skip_args ;
 -- _dl_argc ;
 ++ _dl_argv ;
 }
 else if ( ! strcmp ( _dl_argv [ 1 ] , "--inhibit-cache" ) ) {
 GLRO ( dl_inhibit_cache ) = 1 ;
 ++ _dl_skip_args ;
 -- _dl_argc ;
 ++ _dl_argv ;
 }
 else if ( ! strcmp ( _dl_argv [ 1 ] , "--library-path" ) && _dl_argc > 2 ) {
 library_path = _dl_argv [ 2 ] ;
 _dl_skip_args += 2 ;
 _dl_argc -= 2 ;
 _dl_argv += 2 ;
 }
 else if ( ! strcmp ( _dl_argv [ 1 ] , "--inhibit-rpath" ) && _dl_argc > 2 ) {
 GLRO ( dl_inhibit_rpath ) = _dl_argv [ 2 ] ;
 _dl_skip_args += 2 ;
 _dl_argc -= 2 ;
 _dl_argv += 2 ;
 }
 else if ( ! strcmp ( _dl_argv [ 1 ] , "--audit" ) && _dl_argc > 2 ) {
 process_dl_audit ( _dl_argv [ 2 ] ) ;
 _dl_skip_args += 2 ;
 _dl_argc -= 2 ;
 _dl_argv += 2 ;
 }
 else break ;
 if ( _dl_argc < 2 ) _dl_fatal_printf ( "\ Usage: ld.so [OPTION]... EXECUTABLE-FILE [ARGS-FOR-PROGRAM...]\n\ You have invoked `ld.so', the helper program for shared library executables.\n\ This program usually lives in the file `/lib/ld.so', and special directives\n\ in executable files using ELF shared libraries tell the system's program\n\ loader to load the helper program from this file. This helper program loads\n\ the shared libraries needed by the program executable, prepares the program\n\ to run, and runs it. You may invoke this helper program directly from the\n\ command line to load and run an ELF executable file;
 this is like executing\n\ that file itself, but always uses this helper program from the file you\n\ specified, instead of the helper program file specified in the executable\n\ file you run. This is mostly of use for maintainers to test new versions\n\ of this helper program;
 chances are you did not intend to run this program.\n\ \n\ --list list all dependencies and how they are resolved\n\ --verify verify that given object really is a dynamically linked\n\ object we can handle\n\ --inhibit-cache Do not use " LD_SO_CACHE "\n\ --library-path PATH use given PATH instead of content of the environment\n\ variable LD_LIBRARY_PATH\n\ --inhibit-rpath LIST ignore RUNPATH and RPATH information in object names\n\ in LIST\n\ --audit LIST use objects named in LIST as auditors\n" ) ;
 ++ _dl_skip_args ;
 -- _dl_argc ;
 ++ _dl_argv ;
 for ( ph = phdr ;
 ph < & phdr [ phnum ] ;
 ++ ph ) if ( ph -> p_type == PT_GNU_STACK ) {
 GL ( dl_stack_flags ) = ph -> p_flags ;
 break ;
 }
 if ( __builtin_expect ( mode , normal ) == verify ) {
 const char * objname ;
 const char * err_str = NULL ;
 struct map_args args ;
 bool malloced ;
 args . str = rtld_progname ;
 args . loader = NULL ;
 args . mode = __RTLD_OPENEXEC ;
 ( void ) _dl_catch_error ( & objname , & err_str , & malloced , map_doit , & args ) ;
 if ( __glibc_unlikely ( err_str != NULL ) ) _exit ( EXIT_FAILURE ) ;
 }
 else {
 HP_TIMING_NOW ( start ) ;
 _dl_map_object ( NULL , rtld_progname , lt_executable , 0 , __RTLD_OPENEXEC , LM_ID_BASE ) ;
 HP_TIMING_NOW ( stop ) ;
 HP_TIMING_DIFF ( load_time , start , stop ) ;
 }
 main_map = GL ( dl_ns ) [ LM_ID_BASE ] . _ns_loaded ;
 if ( __builtin_expect ( mode , normal ) == normal && GL ( dl_rtld_map ) . l_info [ DT_SONAME ] != NULL && main_map -> l_info [ DT_SONAME ] != NULL && strcmp ( ( const char * ) D_PTR ( & GL ( dl_rtld_map ) , l_info [ DT_STRTAB ] ) + GL ( dl_rtld_map ) . l_info [ DT_SONAME ] -> d_un . d_val , ( const char * ) D_PTR ( main_map , l_info [ DT_STRTAB ] ) + main_map -> l_info [ DT_SONAME ] -> d_un . d_val ) == 0 ) _dl_fatal_printf ( "loader cannot load itself\n" ) ;
 phdr = main_map -> l_phdr ;
 phnum = main_map -> l_phnum ;
 main_map -> l_name = ( char * ) "" ;
 * user_entry = main_map -> l_entry ;

 av -> a_type != AT_NULL ;
 av ++ ) switch ( av -> a_type ) {
 case AT_PHDR : av -> a_un . a_val = ( uintptr_t ) phdr ;
 break ;
 case AT_PHNUM : av -> a_un . a_val = phnum ;
 break ;
 case AT_ENTRY : av -> a_un . a_val = * user_entry ;
 break ;
 case AT_EXECFN : av -> a_un . a_val = ( uintptr_t ) _dl_argv [ 0 ] ;
 break ;
 }

 else {
 main_map = _dl_new_object ( ( char * ) "" , "" , lt_executable , NULL , __RTLD_OPENEXEC , LM_ID_BASE ) ;
 assert ( main_map != NULL ) ;
 main_map -> l_phdr = phdr ;
 main_map -> l_phnum = phnum ;
 main_map -> l_entry = * user_entry ;
 _dl_add_to_namespace_list ( main_map , LM_ID_BASE ) ;
 assert ( main_map == GL ( dl_ns ) [ LM_ID_BASE ] . _ns_loaded ) ;
 }
 main_map -> l_map_end = 0 ;
 main_map -> l_text_end = 0 ;
 main_map -> l_map_start = ~ 0 ;
 ++ main_map -> l_direct_opencount ;
 for ( ph = phdr ;
 ph < & phdr [ phnum ] ;
 ++ ph ) switch ( ph -> p_type ) {
 case PT_PHDR : main_map -> l_addr = ( ElfW ( Addr ) ) phdr - ph -> p_vaddr ;
 break ;
 case PT_DYNAMIC : main_map -> l_ld = ( void * ) main_map -> l_addr + ph -> p_vaddr ;
 break ;
 case PT_INTERP : _dl_rtld_libname . name = ( ( const char * ) main_map -> l_addr + ph -> p_vaddr ) ;
 GL ( dl_rtld_map ) . l_libname = & _dl_rtld_libname ;
 if ( GL ( dl_rtld_map ) . l_ld == NULL ) {
 const char * p = NULL ;
 const char * cp = _dl_rtld_libname . name ;
 while ( * cp != '\0' ) if ( * cp ++ == '/' ) p = cp ;
 if ( p != NULL ) {
 _dl_rtld_libname2 . name = p ;
 _dl_rtld_libname . next = & _dl_rtld_libname2 ;
 }
 }
 has_interp = true ;
 break ;
 case PT_LOAD : {
 ElfW ( Addr ) mapstart ;
 ElfW ( Addr ) allocend ;
 mapstart = ( main_map -> l_addr + ( ph -> p_vaddr & ~ ( GLRO ( dl_pagesize ) - 1 ) ) ) ;
 if ( main_map -> l_map_start > mapstart ) main_map -> l_map_start = mapstart ;
 allocend = main_map -> l_addr + ph -> p_vaddr + ph -> p_memsz ;
 if ( main_map -> l_map_end < allocend ) main_map -> l_map_end = allocend ;
 if ( ( ph -> p_flags & PF_X ) && allocend > main_map -> l_text_end ) main_map -> l_text_end = allocend ;
 }
 break ;
 case PT_TLS : if ( ph -> p_memsz > 0 ) {
 main_map -> l_tls_blocksize = ph -> p_memsz ;
 main_map -> l_tls_align = ph -> p_align ;
 if ( ph -> p_align == 0 ) main_map -> l_tls_firstbyte_offset = 0 ;
 else main_map -> l_tls_firstbyte_offset = ( ph -> p_vaddr & ( ph -> p_align - 1 ) ) ;
 main_map -> l_tls_initimage_size = ph -> p_filesz ;
 main_map -> l_tls_initimage = ( void * ) ph -> p_vaddr ;
 GL ( dl_tls_max_dtv_idx ) = main_map -> l_tls_modid = 1 ;
 }
 break ;
 case PT_GNU_STACK : GL ( dl_stack_flags ) = ph -> p_flags ;
 break ;
 case PT_GNU_RELRO : main_map -> l_relro_addr = ph -> p_vaddr ;
 main_map -> l_relro_size = ph -> p_memsz ;
 break ;
 }
 if ( main_map -> l_tls_initimage != NULL ) main_map -> l_tls_initimage = ( char * ) main_map -> l_tls_initimage + main_map -> l_addr ;
 if ( ! main_map -> l_map_end ) main_map -> l_map_end = ~ 0 ;
 if ( ! main_map -> l_text_end ) main_map -> l_text_end = ~ 0 ;
 if ( ! GL ( dl_rtld_map ) . l_libname && GL ( dl_rtld_map ) . l_name ) {
 _dl_rtld_libname . name = GL ( dl_rtld_map ) . l_name ;
 GL ( dl_rtld_map ) . l_libname = & _dl_rtld_libname ;
 }
 else assert ( GL ( dl_rtld_map ) . l_libname ) ;
 if ( GL ( dl_rtld_map ) . l_info [ DT_SONAME ] != NULL && strcmp ( GL ( dl_rtld_map ) . l_libname -> name , ( const char * ) D_PTR ( & GL ( dl_rtld_map ) , l_info [ DT_STRTAB ] ) + GL ( dl_rtld_map ) . l_info [ DT_SONAME ] -> d_un . d_val ) != 0 ) {
 static struct libname_list newname ;
 newname . name = ( ( char * ) D_PTR ( & GL ( dl_rtld_map ) , l_info [ DT_STRTAB ] ) + GL ( dl_rtld_map ) . l_info [ DT_SONAME ] -> d_un . d_ptr ) ;
 newname . next = NULL ;
 newname . dont_free = 1 ;
 assert ( GL ( dl_rtld_map ) . l_libname -> next == NULL ) ;
 GL ( dl_rtld_map ) . l_libname -> next = & newname ;
 }
 assert ( GL ( dl_rtld_map ) . l_relocated ) ;
 if ( ! rtld_is_main ) {
 elf_get_dynamic_info ( main_map , NULL ) ;
 _dl_setup_hash ( main_map ) ;
 }
 if ( __builtin_expect ( mode , normal ) == verify ) {
 if ( main_map -> l_ld == NULL ) _exit ( 1 ) ;


 }
 struct link_map * * first_preload = & GL ( dl_rtld_map ) . l_next ;
 setup_vdso ( main_map , & first_preload ) ;


 struct r_debug * r = _dl_debug_initialize ( GL ( dl_rtld_map ) . l_addr , LM_ID_BASE ) ;
 r -> r_state = RT_CONSISTENT ;
 if ( ! GL ( dl_rtld_map ) . l_name ) GL ( dl_rtld_map ) . l_name = ( char * ) GL ( dl_rtld_map ) . l_libname -> name ;
 GL ( dl_rtld_map ) . l_type = lt_library ;
 main_map -> l_next = & GL ( dl_rtld_map ) ;
 GL ( dl_rtld_map ) . l_prev = main_map ;
 ++ GL ( dl_ns ) [ LM_ID_BASE ] . _ns_nloaded ;
 ++ GL ( dl_load_adds ) ;
 if ( GLRO ( dl_use_load_bias ) == ( ElfW ( Addr ) ) - 2 ) GLRO ( dl_use_load_bias ) = main_map -> l_addr == 0 ? - 1 : 0 ;
 const ElfW ( Ehdr ) * rtld_ehdr ;

 rtld_ehdr = & __ehdr_start ;


 assert ( rtld_ehdr -> e_phentsize == sizeof ( ElfW ( Phdr ) ) ) ;
 const ElfW ( Phdr ) * rtld_phdr = ( const void * ) rtld_ehdr + rtld_ehdr -> e_phoff ;
 GL ( dl_rtld_map ) . l_phdr = rtld_phdr ;
 GL ( dl_rtld_map ) . l_phnum = rtld_ehdr -> e_phnum ;
 size_t cnt = rtld_ehdr -> e_phnum ;
 while ( cnt -- > 0 ) if ( rtld_phdr [ cnt ] . p_type == PT_GNU_RELRO ) {
 GL ( dl_rtld_map ) . l_relro_addr = rtld_phdr [ cnt ] . p_vaddr ;
 GL ( dl_rtld_map ) . l_relro_size = rtld_phdr [ cnt ] . p_memsz ;
 break ;
 }
 if ( GL ( dl_rtld_map ) . l_tls_blocksize != 0 ) GL ( dl_rtld_map ) . l_tls_modid = _dl_next_tls_modid ( ) ;
 if ( __glibc_unlikely ( audit_list != NULL ) ) {
 struct audit_ifaces * last_audit = NULL ;
 struct audit_list * al = audit_list -> next ;
 tcbp = init_tls ( ) ;
 security_init ( ) ;
 do {
 int tls_idx = GL ( dl_tls_max_dtv_idx ) ;
 struct dlmopen_args dlmargs ;
 dlmargs . fname = al -> name ;
 dlmargs . map = NULL ;
 const char * objname ;
 const char * err_str = NULL ;
 bool malloced ;
 ( void ) _dl_catch_error ( & objname , & err_str , & malloced , dlmopen_doit , & dlmargs ) ;
 if ( __glibc_unlikely ( err_str != NULL ) ) {
 not_loaded : _dl_error_printf ( "\ ERROR: ld.so: object '%s' cannot be loaded as audit interface: %s;
 ignored.\n" , al -> name , err_str ) ;
 if ( malloced ) free ( ( char * ) err_str ) ;
 }
 else {
 struct lookup_args largs ;
 largs . name = "la_version" ;
 largs . map = dlmargs . map ;
 ( void ) _dl_catch_error ( & objname , & err_str , & malloced , lookup_doit , & largs ) ;
 unsigned int ( * laversion ) ( unsigned int ) ;
 unsigned int lav ;
 if ( err_str == NULL && ( laversion = largs . result ) != NULL && ( lav = laversion ( LAV_CURRENT ) ) > 0 && lav <= LAV_CURRENT ) {
 union {
 struct audit_ifaces ifaces ;

 }
 * newp = malloc ( sizeof ( * newp ) ) ;
 static const char audit_iface_names [ ] = "la_activity\0" "la_objsearch\0" "la_objopen\0" "la_preinit\0" # if __ELF_NATIVE_CLASS == 32 "la_symbind32\0" # elif __ELF_NATIVE_CLASS == 64 "la_symbind64\0" # else # error "__ELF_NATIVE_CLASS must be defined" # endif # define STRING ( s ) __STRING ( s ) "la_" STRING ( ARCH_LA_PLTENTER ) "\0" "la_" STRING ( ARCH_LA_PLTEXIT ) "\0" "la_objclose\0" ;
 unsigned int cnt = 0 ;
 const char * cp = audit_iface_names ;
 do {
 largs . name = cp ;
 ( void ) _dl_catch_error ( & objname , & err_str , & malloced , lookup_doit , & largs ) ;
 if ( err_str == NULL && largs . result != NULL ) {
 newp -> fptr [ cnt ] = largs . result ;
 GL ( dl_rtld_map ) . l_audit [ cnt ] . cookie = ( intptr_t ) & GL ( dl_rtld_map ) ;
 }
 else newp -> fptr [ cnt ] = NULL ;
 ++ cnt ;
 cp = ( char * ) rawmemchr ( cp , '\0' ) + 1 ;
 }
 while ( * cp != '\0' ) ;
 assert ( cnt == naudit_ifaces ) ;
 newp -> ifaces . next = NULL ;
 if ( last_audit == NULL ) last_audit = GLRO ( dl_audit ) = & newp -> ifaces ;
 else last_audit = last_audit -> next = & newp -> ifaces ;
 ++ GLRO ( dl_naudit ) ;
 dlmargs . map -> l_auditing = 1 ;
 }
 else {


 assert ( GL ( dl_ns ) [ ns ] . _ns_loaded == NULL ) ;
 assert ( GL ( dl_ns ) [ ns ] . _ns_nloaded == 0 ) ;
 GL ( dl_tls_max_dtv_idx ) = tls_idx ;
 goto not_loaded ;
 }
 }
 al = al -> next ;
 }
 while ( al != audit_list -> next ) ;
 if ( __glibc_unlikely ( GLRO ( dl_naudit ) > 0 ) ) {
 struct link_map * ls [ 2 ] = {
 main_map , & GL ( dl_rtld_map ) }
 ;
 for ( unsigned int outer = 0 ;
 outer < 2 ;
 ++ outer ) {
 struct audit_ifaces * afct = GLRO ( dl_audit ) ;
 for ( unsigned int cnt = 0 ;
 cnt < GLRO ( dl_naudit ) ;
 ++ cnt ) {
 if ( afct -> objopen != NULL ) {
 ls [ outer ] -> l_audit [ cnt ] . bindflags = afct -> objopen ( ls [ outer ] , LM_ID_BASE , & ls [ outer ] -> l_audit [ cnt ] . cookie ) ;
 ls [ outer ] -> l_audit_any_plt |= ls [ outer ] -> l_audit [ cnt ] . bindflags != 0 ;
 }
 afct = afct -> next ;
 }
 }
 }
 }
 size_t count_modids = _dl_count_modids ( ) ;

 ELF_MACHINE_DEBUG_SETUP ( & GL ( dl_rtld_map ) , r ) ;

 if ( GL ( dl_rtld_map ) . l_info [ DT_DEBUG ] != NULL ) GL ( dl_rtld_map ) . l_info [ DT_DEBUG ] -> d_un . d_ptr = ( ElfW ( Addr ) ) r ;

 _dl_debug_state ( ) ;
 LIBC_PROBE ( init_start , 2 , LM_ID_BASE , r ) ;
 if ( __glibc_unlikely ( GLRO ( dl_naudit ) > 0 ) ) {
 struct audit_ifaces * afct = GLRO ( dl_audit ) ;
 for ( unsigned int cnt = 0 ;
 cnt < GLRO ( dl_naudit ) ;
 ++ cnt ) {
 if ( afct -> activity != NULL ) afct -> activity ( & main_map -> l_audit [ cnt ] . cookie , LA_ACT_ADD ) ;
 afct = afct -> next ;
 }
 }
 assert ( * first_preload == NULL ) ;
 struct link_map * * preloads = NULL ;
 unsigned int npreloads = 0 ;
 if ( __glibc_unlikely ( preloadlist != NULL ) ) {
 char * list = strdupa ( preloadlist ) ;
 char * p ;
 HP_TIMING_NOW ( start ) ;
 while ( ( p = ( strsep ) ( & list , " :" ) ) != NULL ) if ( p [ 0 ] != '\0' && ( __builtin_expect ( ! __libc_enable_secure , 1 ) || strchr ( p , '/' ) == NULL ) ) npreloads += do_preload ( p , main_map , "LD_PRELOAD" ) ;
 HP_TIMING_NOW ( stop ) ;
 HP_TIMING_DIFF ( diff , start , stop ) ;
 HP_TIMING_ACCUM_NT ( load_time , diff ) ;
 }
 static const char preload_file [ ] = "/etc/ld.so.preload" ;
 if ( __glibc_unlikely ( __access ( preload_file , R_OK ) == 0 ) ) {
 file = _dl_sysdep_read_whole_file ( preload_file , & file_size , PROT_READ | PROT_WRITE ) ;
 if ( __glibc_unlikely ( file != MAP_FAILED ) ) {
 char * problem ;
 char * runp ;
 size_t rest ;
 runp = file ;
 rest = file_size ;
 while ( rest > 0 ) {
 char * comment = memchr ( runp , '#' , rest ) ;
 if ( comment == NULL ) break ;
 rest -= comment - runp ;
 do * comment = ' ' ;
 while ( -- rest > 0 && * ++ comment != '\n' ) ;
 }
 if ( file [ file_size - 1 ] != ' ' && file [ file_size - 1 ] != '\t' && file [ file_size - 1 ] != '\n' && file [ file_size - 1 ] != ':' ) {
 problem = & file [ file_size ] ;
 while ( problem > file && problem [ - 1 ] != ' ' && problem [ - 1 ] != '\t' && problem [ - 1 ] != '\n' && problem [ - 1 ] != ':' ) -- problem ;
 if ( problem > file ) problem [ - 1 ] = '\0' ;
 }
 else {
 problem = NULL ;
 file [ file_size - 1 ] = '\0' ;
 }
 HP_TIMING_NOW ( start ) ;
 if ( file != problem ) {
 char * p ;
 runp = file ;
 while ( ( p = strsep ( & runp , ": \t\n" ) ) != NULL ) if ( p [ 0 ] != '\0' ) npreloads += do_preload ( p , main_map , preload_file ) ;
 }
 if ( problem != NULL ) {
 char * p = strndupa ( problem , file_size - ( problem - file ) ) ;
 npreloads += do_preload ( p , main_map , preload_file ) ;
 }
 HP_TIMING_NOW ( stop ) ;
 HP_TIMING_DIFF ( diff , start , stop ) ;
 HP_TIMING_ACCUM_NT ( load_time , diff ) ;
 __munmap ( file , file_size ) ;
 }
 }
 if ( __glibc_unlikely ( * first_preload != NULL ) ) {
 struct link_map * l = * first_preload ;
 preloads = __alloca ( npreloads * sizeof preloads [ 0 ] ) ;
 i = 0 ;
 do {
 preloads [ i ++ ] = l ;
 l = l -> l_next ;
 }
 while ( l ) ;
 assert ( i == npreloads ) ;
 }
 HP_TIMING_NOW ( start ) ;
 _dl_map_object_deps ( main_map , preloads , npreloads , mode == trace , 0 ) ;
 HP_TIMING_NOW ( stop ) ;
 HP_TIMING_DIFF ( diff , start , stop ) ;
 HP_TIMING_ACCUM_NT ( load_time , diff ) ;
 for ( i = main_map -> l_searchlist . r_nlist ;
 i > 0 ;
 ) main_map -> l_searchlist . r_list [ -- i ] -> l_global = 1 ;
 GL ( dl_rtld_map ) . l_prev -> l_next = GL ( dl_rtld_map ) . l_next ;
 if ( GL ( dl_rtld_map ) . l_next != NULL ) GL ( dl_rtld_map ) . l_next -> l_prev = GL ( dl_rtld_map ) . l_prev ;
 for ( i = 1 ;
 i < main_map -> l_searchlist . r_nlist ;
 ++ i ) if ( main_map -> l_searchlist . r_list [ i ] == & GL ( dl_rtld_map ) ) break ;
 bool rtld_multiple_ref = false ;
 if ( __glibc_likely ( i < main_map -> l_searchlist . r_nlist ) ) {
 rtld_multiple_ref = true ;
 GL ( dl_rtld_map ) . l_prev = main_map -> l_searchlist . r_list [ i - 1 ] ;
 if ( __builtin_expect ( mode , normal ) == normal ) {
 GL ( dl_rtld_map ) . l_next = ( i + 1 < main_map -> l_searchlist . r_nlist ? main_map -> l_searchlist . r_list [ i + 1 ] : NULL ) ;


 else GL ( dl_rtld_map ) . l_next = GL ( dl_rtld_map ) . l_prev -> l_next ;
 assert ( GL ( dl_rtld_map ) . l_prev -> l_next == GL ( dl_rtld_map ) . l_next ) ;
 GL ( dl_rtld_map ) . l_prev -> l_next = & GL ( dl_rtld_map ) ;
 if ( GL ( dl_rtld_map ) . l_next != NULL ) {
 assert ( GL ( dl_rtld_map ) . l_next -> l_prev == GL ( dl_rtld_map ) . l_prev ) ;
 GL ( dl_rtld_map ) . l_next -> l_prev = & GL ( dl_rtld_map ) ;
 }
 }
 {
 struct version_check_args args ;
 args . doexit = mode == normal ;
 args . dotrace = mode == trace ;
 _dl_receive_error ( print_missing_version , version_check_doit , & args ) ;
 }
 bool was_tls_init_tp_called = tls_init_tp_called ;
 if ( tcbp == NULL ) tcbp = init_tls ( ) ;
 if ( __glibc_likely ( audit_list == NULL ) ) security_init ( ) ;
 if ( __builtin_expect ( mode , normal ) != normal ) {
 struct link_map * l ;
 if ( GLRO ( dl_debug_mask ) & DL_DEBUG_PRELINK ) {
 struct r_scope_elem * scope = & main_map -> l_searchlist ;
 for ( i = 0 ;
 i < scope -> r_nlist ;
 i ++ ) {
 l = scope -> r_list [ i ] ;
 if ( l -> l_faked ) {
 _dl_printf ( "\t%s => not found\n" , l -> l_libname -> name ) ;
 continue ;
 }
 if ( _dl_name_match_p ( GLRO ( dl_trace_prelink ) , l ) ) GLRO ( dl_trace_prelink_map ) = l ;
 _dl_printf ( "\t%s => %s (0x%0*Zx, 0x%0*Zx)" , DSO_FILENAME ( l -> l_libname -> name ) , DSO_FILENAME ( l -> l_name ) , ( int ) sizeof l -> l_map_start * 2 , ( size_t ) l -> l_map_start , ( int ) sizeof l -> l_addr * 2 , ( size_t ) l -> l_addr ) ;
 if ( l -> l_tls_modid ) _dl_printf ( " TLS(0x%Zx, 0x%0*Zx)\n" , l -> l_tls_modid , ( int ) sizeof l -> l_tls_offset * 2 , ( size_t ) l -> l_tls_offset ) ;
 else _dl_printf ( "\n" ) ;
 }
 }
 else if ( GLRO ( dl_debug_mask ) & DL_DEBUG_UNUSED ) {
 struct link_map * l = main_map ;
 struct relocate_args args = {
 . l = l , . reloc_mode = ( ( GLRO ( dl_lazy ) ? RTLD_LAZY : 0 ) | __RTLD_NOIFUNC ) }
 ;
 _dl_receive_error ( print_unresolved , relocate_doit , & args ) ;
 ElfW ( Dyn ) * dyn = main_map -> l_ld ;
 bool first = true ;
 while ( dyn -> d_tag != DT_NULL ) {
 if ( dyn -> d_tag == DT_NEEDED ) {
 l = l -> l_next ;


 if ( first ) {
 _dl_printf ( "Unused direct dependencies:\n" ) ;
 first = false ;
 }
 _dl_printf ( "\t%s\n" , l -> l_name ) ;
 }
 }
 ++ dyn ;
 }
 _exit ( first != true ) ;
 }
 else if ( ! main_map -> l_info [ DT_NEEDED ] ) _dl_printf ( "\tstatically linked\n" ) ;
 else {
 for ( l = main_map -> l_next ;
 l ;
 l = l -> l_next ) if ( l -> l_faked ) _dl_printf ( "\t%s => not found\n" , l -> l_libname -> name ) ;
 else if ( strcmp ( l -> l_libname -> name , l -> l_name ) == 0 ) _dl_printf ( "\t%s (0x%0*Zx)\n" , l -> l_libname -> name , ( int ) sizeof l -> l_map_start * 2 , ( size_t ) l -> l_map_start ) ;
 else _dl_printf ( "\t%s => %s (0x%0*Zx)\n" , l -> l_libname -> name , l -> l_name , ( int ) sizeof l -> l_map_start * 2 , ( size_t ) l -> l_map_start ) ;
 }
 if ( __builtin_expect ( mode , trace ) != trace ) for ( i = 1 ;
 i < ( unsigned int ) _dl_argc ;
 ++ i ) {
 const ElfW ( Sym ) * ref = NULL ;
 ElfW ( Addr ) loadbase ;
 lookup_t result ;
 result = _dl_lookup_symbol_x ( _dl_argv [ i ] , main_map , & ref , main_map -> l_scope , NULL , ELF_RTYPE_CLASS_PLT , DL_LOOKUP_ADD_DEPENDENCY , NULL ) ;
 loadbase = LOOKUP_VALUE_ADDRESS ( result ) ;
 _dl_printf ( "%s found at 0x%0*Zd in object at 0x%0*Zd\n" , _dl_argv [ i ] , ( int ) sizeof ref -> st_value * 2 , ( size_t ) ref -> st_value , ( int ) sizeof loadbase * 2 , ( size_t ) loadbase ) ;
 }
 else {
 if ( GLRO ( dl_lazy ) >= 0 && GLRO ( dl_verbose ) ) {
 struct relocate_args args ;
 unsigned int i ;
 args . reloc_mode = ( ( GLRO ( dl_lazy ) ? RTLD_LAZY : 0 ) | __RTLD_NOIFUNC ) ;
 i = main_map -> l_searchlist . r_nlist ;
 while ( i -- > 0 ) {
 struct link_map * l = main_map -> l_initfini [ i ] ;
 if ( l != & GL ( dl_rtld_map ) && ! l -> l_faked ) {
 args . l = l ;
 _dl_receive_error ( print_unresolved , relocate_doit , & args ) ;
 }
 }
 if ( ( GLRO ( dl_debug_mask ) & DL_DEBUG_PRELINK ) && rtld_multiple_ref ) {
 GL ( dl_rtld_map ) . l_relocated = 0 ;
 _dl_relocate_object ( & GL ( dl_rtld_map ) , main_map -> l_scope , __RTLD_NOIFUNC , 0 ) ;
 }
 }

 int first = 1 ;
 struct link_map * map ;
 for ( map = main_map ;
 map != NULL ;
 map = map -> l_next ) {
 const char * strtab ;
 ElfW ( Dyn ) * dyn = map -> l_info [ VERNEEDTAG ] ;
 ElfW ( Verneed ) * ent ;
 if ( dyn == NULL ) continue ;
 strtab = ( const void * ) D_PTR ( map , l_info [ DT_STRTAB ] ) ;
 ent = ( ElfW ( Verneed ) * ) ( map -> l_addr + dyn -> d_un . d_ptr ) ;
 if ( first ) {
 _dl_printf ( "\n\tVersion information:\n" ) ;
 first = 0 ;
 }
 _dl_printf ( "\t%s:\n" , DSO_FILENAME ( map -> l_name ) ) ;
 while ( 1 ) {
 ElfW ( Vernaux ) * aux ;
 struct link_map * needed ;
 needed = find_needed ( strtab + ent -> vn_file ) ;
 aux = ( ElfW ( Vernaux ) * ) ( ( char * ) ent + ent -> vn_aux ) ;
 while ( 1 ) {
 const char * fname = NULL ;
 if ( needed != NULL && match_version ( strtab + aux -> vna_name , needed ) ) fname = needed -> l_name ;
 _dl_printf ( "\t\t%s (%s) %s=> %s\n" , strtab + ent -> vn_file , strtab + aux -> vna_name , aux -> vna_flags & VER_FLG_WEAK ? "[WEAK] " : "" , fname ? : "not found" ) ;
 if ( aux -> vna_next == 0 ) break ;
 aux = ( ElfW ( Vernaux ) * ) ( ( char * ) aux + aux -> vna_next ) ;
 }
 if ( ent -> vn_next == 0 ) break ;
 ent = ( ElfW ( Verneed ) * ) ( ( char * ) ent + ent -> vn_next ) ;
 }
 }
 }
 }
 _exit ( 0 ) ;
 }
 if ( main_map -> l_info [ ADDRIDX ( DT_GNU_LIBLIST ) ] && ! __builtin_expect ( GLRO ( dl_profile ) != NULL , 0 ) && ! __builtin_expect ( GLRO ( dl_dynamic_weak ) , 0 ) ) {
 ElfW ( Lib ) * liblist , * liblistend ;
 struct link_map * * r_list , * * r_listend , * l ;
 const char * strtab = ( const void * ) D_PTR ( main_map , l_info [ DT_STRTAB ] ) ;
 assert ( main_map -> l_info [ VALIDX ( DT_GNU_LIBLISTSZ ) ] != NULL ) ;
 liblist = ( ElfW ( Lib ) * ) main_map -> l_info [ ADDRIDX ( DT_GNU_LIBLIST ) ] -> d_un . d_ptr ;
 liblistend = ( ElfW ( Lib ) * ) ( ( char * ) liblist + main_map -> l_info [ VALIDX ( DT_GNU_LIBLISTSZ ) ] -> d_un . d_val ) ;
 r_list = main_map -> l_searchlist . r_list ;
 r_listend = r_list + main_map -> l_searchlist . r_nlist ;
 for ( ;
 r_list < r_listend && liblist < liblistend ;
 r_list ++ ) {
 l = * r_list ;
 if ( l == main_map ) continue ;
 if ( l -> l_addr ) break ;
 if ( l -> l_info [ VALIDX ( DT_CHECKSUM ) ] == NULL || l -> l_info [ VALIDX ( DT_CHECKSUM ) ] -> d_un . d_val != liblist -> l_checksum ) break ;
 if ( l -> l_info [ VALIDX ( DT_GNU_PRELINKED ) ] == NULL || l -> l_info [ VALIDX ( DT_GNU_PRELINKED ) ] -> d_un . d_val != liblist -> l_time_stamp ) break ;
 if ( ! _dl_name_match_p ( strtab + liblist -> l_name , l ) ) break ;
 ++ liblist ;
 }
 if ( r_list == r_listend && liblist == liblistend ) prelinked = true ;
 if ( __glibc_unlikely ( GLRO ( dl_debug_mask ) & DL_DEBUG_LIBS ) ) _dl_debug_printf ( "\nprelink checking: %s\n" , prelinked ? "ok" : "failed" ) ;
 }
 GL ( dl_ns ) [ LM_ID_BASE ] . _ns_main_searchlist = & main_map -> l_searchlist ;
 GLRO ( dl_initial_searchlist ) = * GL ( dl_ns ) [ LM_ID_BASE ] . _ns_main_searchlist ;
 GLRO ( dl_init_all_dirs ) = GL ( dl_all_dirs ) ;
 if ( __glibc_unlikely ( GLRO ( dl_debug_mask ) & DL_DEBUG_SCOPES ) ) {
 _dl_debug_printf ( "\nInitial object scopes\n" ) ;
 for ( struct link_map * l = main_map ;
 l != NULL ;
 l = l -> l_next ) _dl_show_scope ( l , 0 ) ;
 }
 if ( prelinked ) {
 if ( main_map -> l_info [ ADDRIDX ( DT_GNU_CONFLICT ) ] != NULL ) {
 ElfW ( Rela ) * conflict , * conflictend ;

 hp_timing_t stop ;

 assert ( main_map -> l_info [ VALIDX ( DT_GNU_CONFLICTSZ ) ] != NULL ) ;
 conflict = ( ElfW ( Rela ) * ) main_map -> l_info [ ADDRIDX ( DT_GNU_CONFLICT ) ] -> d_un . d_ptr ;
 conflictend = ( ElfW ( Rela ) * ) ( ( char * ) conflict + main_map -> l_info [ VALIDX ( DT_GNU_CONFLICTSZ ) ] -> d_un . d_val ) ;
 _dl_resolve_conflicts ( main_map , conflict , conflictend ) ;
 HP_TIMING_NOW ( stop ) ;
 HP_TIMING_DIFF ( relocate_time , start , stop ) ;
 }
 for ( struct link_map * l = main_map ;
 l != NULL ;
 l = l -> l_next ) {
 l -> l_relocated = 1 ;
 if ( l -> l_relro_size ) _dl_protect_relro ( l ) ;
 if ( l -> l_tls_blocksize != 0 && tls_init_tp_called ) _dl_add_to_slotinfo ( l ) ;
 }
 }
 else {
 int consider_profiling = GLRO ( dl_profile ) != NULL ;

 hp_timing_t stop ;

 HP_TIMING_NOW ( start ) ;
 unsigned i = main_map -> l_searchlist . r_nlist ;
 while ( i -- > 0 ) {
 struct link_map * l = main_map -> l_initfini [ i ] ;
 struct libname_list * lnp = l -> l_libname -> next ;
 while ( __builtin_expect ( lnp != NULL , 0 ) ) {
 lnp -> dont_free = 1 ;
 lnp = lnp -> next ;
 }
 l -> l_free_initfini = 0 ;
 if ( l != & GL ( dl_rtld_map ) ) _dl_relocate_object ( l , l -> l_scope , GLRO ( dl_lazy ) ? RTLD_LAZY : 0 , consider_profiling ) ;
 if ( l -> l_tls_blocksize != 0 && tls_init_tp_called ) _dl_add_to_slotinfo ( l ) ;
 }
 HP_TIMING_NOW ( stop ) ;
 HP_TIMING_DIFF ( relocate_time , start , stop ) ;
 if ( __glibc_unlikely ( GL ( dl_profile_map ) != NULL ) ) _dl_start_profile ( ) ;
 }
 if ( ( ! was_tls_init_tp_called && GL ( dl_tls_max_dtv_idx ) > 0 ) || count_modids != _dl_count_modids ( ) ) ++ GL ( dl_tls_generation ) ;
 _dl_allocate_tls_init ( tcbp ) ;
 if ( ! tls_init_tp_called ) {
 const char * lossage = TLS_INIT_TP ( tcbp ) ;
 if ( __glibc_unlikely ( lossage != NULL ) ) _dl_fatal_printf ( "cannot set up thread-local storage: %s\n" , lossage ) ;
 }
 assert ( GLRO ( dl_init_all_dirs ) == GL ( dl_all_dirs ) ) ;
 if ( ! prelinked && rtld_multiple_ref ) {

 hp_timing_t stop ;
 hp_timing_t add ;

 GL ( dl_rtld_map ) . l_relocated = 0 ;
 _dl_relocate_object ( & GL ( dl_rtld_map ) , main_map -> l_scope , 0 , 0 ) ;
 HP_TIMING_NOW ( stop ) ;
 HP_TIMING_DIFF ( add , start , stop ) ;
 HP_TIMING_ACCUM_NT ( relocate_time , add ) ;
 }
 _dl_sysdep_start_cleanup ( ) ;

 struct link_map * head = GL ( dl_ns ) [ LM_ID_BASE ] . _ns_loaded ;
 if ( head -> l_auditing == 0 ) {
 struct audit_ifaces * afct = GLRO ( dl_audit ) ;
 for ( unsigned int cnt = 0 ;
 cnt < GLRO ( dl_naudit ) ;
 ++ cnt ) {
 if ( afct -> activity != NULL ) afct -> activity ( & head -> l_audit [ cnt ] . cookie , LA_ACT_CONSISTENT ) ;
 afct = afct -> next ;
 }
 }
 }

 r -> r_state = RT_CONSISTENT ;
 _dl_debug_state ( ) ;
 LIBC_PROBE ( init_complete , 2 , LM_ID_BASE , r ) ;

