int pg_regcomp ( regex_t * re , const chr * string , size_t len , int flags , Oid collation ) {
 struct vars var ;
 struct vars * v = & var ;
 struct guts * g ;
 int i ;
 size_t j ;



 if ( ISERR ( ) ) return freev ( v , v -> err ) ;
 }
 if ( re == NULL || string == NULL ) return REG_INVARG ;
 if ( ( flags & REG_QUOTE ) && ( flags & ( REG_ADVANCED | REG_EXPANDED | REG_NEWLINE ) ) ) return REG_INVARG ;
 if ( ! ( flags & REG_EXTENDED ) && ( flags & REG_ADVF ) ) return REG_INVARG ;
 pg_set_regex_collation ( collation ) ;
 v -> re = re ;
 v -> now = string ;
 v -> stop = v -> now + len ;
 v -> savenow = v -> savestop = NULL ;
 v -> err = 0 ;
 v -> cflags = flags ;
 v -> nsubexp = 0 ;
 v -> subs = v -> sub10 ;
 v -> nsubs = 10 ;
 for ( j = 0 ;
 j < v -> nsubs ;
 j ++ ) v -> subs [ j ] = NULL ;
 v -> nfa = NULL ;
 v -> cm = NULL ;
 v -> nlcolor = COLORLESS ;
 v -> wordchrs = NULL ;
 v -> tree = NULL ;
 v -> treechain = NULL ;
 v -> treefree = NULL ;
 v -> cv = NULL ;
 v -> cv2 = NULL ;
 v -> lacons = NULL ;
 v -> nlacons = 0 ;
 v -> spaceused = 0 ;
 re -> re_magic = REMAGIC ;
 re -> re_info = 0 ;
 re -> re_csize = sizeof ( chr ) ;
 re -> re_collation = collation ;
 re -> re_guts = NULL ;
 re -> re_fns = VS ( & functions ) ;
 re -> re_guts = VS ( MALLOC ( sizeof ( struct guts ) ) ) ;
 if ( re -> re_guts == NULL ) return freev ( v , REG_ESPACE ) ;
 g = ( struct guts * ) re -> re_guts ;
 g -> tree = NULL ;
 initcm ( v , & g -> cmap ) ;
 v -> cm = & g -> cmap ;
 g -> lacons = NULL ;
 g -> nlacons = 0 ;
 ZAPCNFA ( g -> search ) ;
 v -> nfa = newnfa ( v , v -> cm , ( struct nfa * ) NULL ) ;
 CNOERR ( ) ;
 v -> cv = newcvec ( 100 , 20 ) ;
 if ( v -> cv == NULL ) return freev ( v , REG_ESPACE ) ;
 lexstart ( v ) ;
 if ( ( v -> cflags & REG_NLSTOP ) || ( v -> cflags & REG_NLANCH ) ) {
 v -> nlcolor = subcolor ( v -> cm , newline ( ) ) ;
 okcolors ( v -> nfa , v -> cm ) ;
 }
 CNOERR ( ) ;
 v -> tree = parse ( v , EOS , PLAIN , v -> nfa -> init , v -> nfa -> final ) ;
 assert ( SEE ( EOS ) ) ;
 CNOERR ( ) ;
 assert ( v -> tree != NULL ) ;
 specialcolors ( v -> nfa ) ;
 CNOERR ( ) ;

 fprintf ( debug , "\n\n\n========= RAW ==========\n" ) ;
 dumpnfa ( v -> nfa , debug ) ;
 dumpst ( v -> tree , debug , 1 ) ;
 }

 v -> ntree = numst ( v -> tree , 1 ) ;
 markst ( v -> tree ) ;
 cleanst ( v ) ;

 fprintf ( debug , "\n\n\n========= TREE FIXED ==========\n" ) ;
 dumpst ( v -> tree , debug , 1 ) ;
 }

 CNOERR ( ) ;
 assert ( v -> nlacons == 0 || v -> lacons != NULL ) ;
 for ( i = 1 ;
 i < v -> nlacons ;
 i ++ ) {
 struct subre * lasub = & v -> lacons [ i ] ;


 }
 CNOERR ( ) ;
 if ( v -> tree -> flags & SHORTER ) NOTE ( REG_USHORTEST ) ;


 CNOERR ( ) ;
 makesearch ( v , v -> nfa ) ;
 CNOERR ( ) ;
 compact ( v -> nfa , & g -> search ) ;
 CNOERR ( ) ;
 re -> re_nsub = v -> nsubexp ;
 v -> re = NULL ;
 g -> magic = GUTSMAGIC ;
 g -> cflags = v -> cflags ;
 g -> info = re -> re_info ;
 g -> nsub = re -> re_nsub ;
 g -> tree = v -> tree ;
 v -> tree = NULL ;
 g -> ntree = v -> ntree ;
 g -> compare = ( v -> cflags & REG_ICASE ) ? casecmp : cmp ;
 g -> lacons = v -> lacons ;
 v -> lacons = NULL ;
 g -> nlacons = v -> nlacons ;


 return freev ( v , 0 ) ;
 }