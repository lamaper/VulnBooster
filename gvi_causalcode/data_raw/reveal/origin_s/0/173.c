void OS2FigureCodePages ( SplineFont * sf , uint32 CodePage [ 2 ] ) {
 int i ;
 uint32 latin1 [ 8 ] ;
 int has_ascii , has_lineart = 0 , has_radical = 0 , has_summation = 0 ;
 int cp852 = 0 , cp775 = 0 , cp861 = 0 , cp860 = 0 , cp857 = 0 , cp855 = 0 , cp862 = 0 , cp863 = 0 ;
 int cp864 = 0 , cp865 = 0 , cp866 = 0 , cp869 = 0 , cp737 = 0 , cp708 = 0 , mac = 0 ;
 int k ;
 SplineChar * sc ;
 SplineFont * sub ;
 memset ( latin1 , 0 , sizeof ( latin1 ) ) ;
 k = 0 ;
 do {
 sub = k < sf -> subfontcnt ? sf -> subfonts [ k ] : sf ;
 for ( i = 0 ;
 i < sub -> glyphcnt ;
 ++ i ) if ( ( sc = sub -> glyphs [ i ] ) != NULL ) {
 if ( sc -> unicodeenc < 256 && sc -> unicodeenc >= 0 ) latin1 [ ( sc -> unicodeenc >> 5 ) ] |= 1 << ( sc -> unicodeenc & 31 ) ;
 }
 ++ k ;
 }
 while ( k < sf -> subfontcnt ) ;
 has_ascii = latin1 [ 1 ] == 0xffffffff && latin1 [ 2 ] == 0xffffffff && ( latin1 [ 3 ] & 0x7fffffff ) == 0x7fffffff ;
 CodePage [ 0 ] = CodePage [ 1 ] = 0 ;
 k = 0 ;
 do {
 sub = k < sf -> subfontcnt ? sf -> subfonts [ k ] : sf ;
 for ( i = 0 ;
 i < sub -> glyphcnt ;
 ++ i ) if ( ( sc = sub -> glyphs [ i ] ) != NULL ) {
 int uni = sc -> unicodeenc ;
 if ( uni == 0xde && has_ascii ) CodePage [ 0 ] |= 1 << 0 ;
 else if ( uni == 0x255a && has_ascii ) {
 CodePage [ 1 ] |= 1U << 30 ;
 CodePage [ 1 ] |= 1U << 31 ;
 }
 else if ( uni == 0x13d && has_ascii ) {
 CodePage [ 0 ] |= 1 << 1 ;
 ++ cp852 ;
 }
 else if ( uni == 0x411 ) {
 CodePage [ 0 ] |= 1 << 2 ;
 ++ cp866 ;
 ++ cp855 ;
 }
 else if ( uni == 0x405 ) {
 ++ cp855 ;
 }
 else if ( uni == 0x386 ) {
 CodePage [ 0 ] |= 1 << 3 ;
 ++ cp869 ;
 ++ cp737 ;
 }
 else if ( uni == 0x130 && has_ascii ) {
 CodePage [ 0 ] |= 1 << 4 ;
 ++ cp857 ;
 }
 else if ( uni == 0x5d0 ) {
 CodePage [ 0 ] |= 1 << 5 ;
 ++ cp862 ;
 }
 else if ( uni == 0x631 ) {
 CodePage [ 0 ] |= 1 << 6 ;
 ++ cp864 ;
 ++ cp708 ;
 }
 else if ( uni == 0x157 && has_ascii ) {
 CodePage [ 0 ] |= 1 << 7 ;
 ++ cp775 ;
 }
 else if ( uni == 0x20AB && has_ascii ) {
 CodePage [ 0 ] |= 1 << 8 ;
 }
 else if ( uni == 0xe45 ) CodePage [ 0 ] |= 1 << 16 ;
 else if ( uni == 0x30a8 ) CodePage [ 0 ] |= 1 << 17 ;
 else if ( uni == 0x3105 ) CodePage [ 0 ] |= 1 << 18 ;
 else if ( uni == 0x3131 ) CodePage [ 0 ] |= 1 << 19 ;
 else if ( uni == 0x592E ) CodePage [ 0 ] |= 1 << 20 ;
 else if ( uni == 0xacf4 ) CodePage [ 0 ] |= 1 << 21 ;
 else if ( uni == 0x2030 && has_ascii ) ++ mac ;
 else if ( uni == 0x2665 && has_ascii ) CodePage [ 0 ] |= 1U << 30 ;
 else if ( uni >= 0xf000 && uni <= 0xf0ff ) CodePage [ 0 ] |= 1U << 31 ;
 else if ( uni == 0xc5 && has_ascii ) ++ cp865 ;
 else if ( uni == 0xe9 && has_ascii ) ++ cp863 ;
 else if ( uni == 0xf5 && has_ascii ) ++ cp860 ;
 else if ( uni == 0xfe && has_ascii ) ++ cp861 ;
 else if ( uni == 0x2524 ) ++ has_lineart ;
 else if ( uni == 0x255c ) ++ cp866 ;
 else if ( uni == 0xbd ) ++ cp869 ;
 else if ( uni == 0x221A ) has_radical = true ;
 else if ( uni == 0x2211 ) has_summation = true ;
 }
 ++ k ;
 }
 while ( k < sf -> subfontcnt ) ;
 if ( cp852 && has_lineart ) CodePage [ 1 ] |= 1 << 26 ;
 if ( cp775 && has_lineart ) CodePage [ 1 ] |= 1 << 27 ;
 if ( cp861 && has_lineart ) CodePage [ 1 ] |= 1 << 22 ;
 if ( cp866 == 2 && has_lineart ) CodePage [ 1 ] |= 1 << 17 ;
 if ( cp855 == 2 && has_lineart ) CodePage [ 1 ] |= 1 << 25 ;
 if ( cp869 == 2 && has_lineart ) CodePage [ 1 ] |= 1 << 16 ;
 if ( cp737 && has_lineart && has_radical ) CodePage [ 1 ] |= 1 << 28 ;
 if ( cp857 && has_lineart ) CodePage [ 1 ] |= 1 << 24 ;
 if ( cp862 && has_lineart && has_radical ) CodePage [ 1 ] |= 1 << 21 ;
 if ( cp864 && has_radical ) CodePage [ 1 ] |= 1 << 19 ;
 if ( cp708 && has_lineart ) CodePage [ 1 ] |= 1 << 29 ;
 if ( cp863 && has_lineart && has_radical ) CodePage [ 1 ] |= 1 << 20 ;
 if ( cp865 && has_lineart && has_radical ) CodePage [ 1 ] |= 1 << 18 ;
 if ( cp860 && has_lineart && has_radical ) CodePage [ 1 ] |= 1 << 23 ;
 if ( mac && has_summation ) CodePage [ 0 ] |= 1U << 29 ;
 }