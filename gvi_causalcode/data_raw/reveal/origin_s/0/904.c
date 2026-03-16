int unupack399 ( char * bs , uint32_t bl , uint32_t init_eax , char * init_ebx , uint32_t init_ecx , char * init_edi , char * end_edi , uint32_t shlsize , char * paddr ) {
 struct lzmastate p ;
 uint32_t loc_eax , ret , loc_al , loc_ecx = init_ecx , loc_ebp , eax_copy = init_eax , temp , i , jakas_kopia ;
 uint32_t state [ 6 ] , temp_ebp ;
 char * loc_edx , * loc_ebx = init_ebx , * loc_edi = init_edi , * loc_ebp8 , * edi_copy ;
 p . p0 = paddr ;
 p . p1 = cli_readint32 ( init_ebx ) ;
 p . p2 = cli_readint32 ( init_ebx + 4 ) ;
 cli_dbgmsg ( "\n\tp0: %p\n\tp1: %08x\n\tp2: %08x\n" , p . p0 , p . p1 , p . p2 ) ;
 for ( i = 0 ;
 i < 6 ;
 i ++ ) {
 state [ i ] = cli_readint32 ( loc_ebx + ( i << 2 ) ) ;
 cli_dbgmsg ( "state[%d] = %08x\n" , i , state [ i ] ) ;
 }
 do {
 loc_eax = eax_copy ;
 loc_edx = loc_ebx + ( loc_eax << 2 ) + 0x58 ;
 if ( ( ret = lzma_upack_esi_00 ( & p , loc_edx , bs , bl ) ) ) {
 loc_al = loc_eax & 0xff ;
 loc_al = ( ( loc_al + 0xf9 ) > 0xff ) ? ( 3 + 8 ) : 8 ;
 loc_eax = ( loc_eax & 0xffffff00 ) | ( loc_al & 0xff ) ;
 loc_ebp = state [ 2 ] ;
 loc_ecx = ( loc_ecx & 0xffffff00 ) | 0x30 ;
 loc_edx += loc_ecx ;
 if ( ! ( ret = lzma_upack_esi_00 ( & p , loc_edx , bs , bl ) ) ) {
 loc_eax -- ;
 temp_ebp = loc_ebp ;
 loc_ebp = state [ 4 ] ;
 state [ 4 ] = state [ 3 ] ;
 state [ 3 ] = temp_ebp ;
 eax_copy = loc_eax ;
 loc_edx = loc_ebx + 0xbc0 ;
 state [ 5 ] = loc_ebp ;
 if ( lzma_upack_esi_54 ( & p , loc_eax , & loc_ecx , & loc_edx , & temp , bs , bl ) == 0xffffffff ) return - 1 ;
 loc_ecx = 3 ;
 jakas_kopia = temp ;
 loc_eax = temp - 1 ;
 if ( loc_eax >= loc_ecx ) loc_eax = loc_ecx ;
 loc_ecx = 0x40 ;
 loc_eax <<= 6 ;
 loc_ebp8 = loc_ebx + ( ( loc_eax << 2 ) + 0x378 ) ;
 if ( lzma_upack_esi_50 ( & p , 1 , loc_ecx , & loc_edx , loc_ebp8 , & loc_eax , bs , bl ) == 0xffffffff ) return - 1 ;
 loc_ebp = loc_eax ;
 if ( ( loc_eax & 0xff ) >= 4 ) {
 loc_ebp = 2 + ( loc_eax & 1 ) ;
 loc_eax >>= 1 ;
 loc_eax -- ;
 temp_ebp = loc_eax ;
 loc_eax = loc_ecx ;
 loc_ecx = temp_ebp ;
 loc_ebp <<= ( loc_ecx & 0xff ) ;
 loc_edx = loc_ebx + ( loc_ebp << 2 ) + 0x178 ;
 if ( ( loc_ecx & 0xff ) > 5 ) {
 loc_ecx = ( loc_ecx & 0xffffff00 ) | ( ( ( loc_ecx & 0xff ) - 4 ) & 0xff ) ;
 loc_eax = 0 ;
 do {
 uint32_t temp_edx ;
 if ( ! CLI_ISCONTAINED ( bs , bl , p . p0 , 4 ) ) return - 1 ;
 temp_edx = cli_readint32 ( ( char * ) p . p0 ) ;
 temp_edx = EC32 ( CE32 ( temp_edx ) ) ;
 p . p1 >>= 1 ;
 temp_edx -= p . p2 ;
 loc_eax <<= 1 ;
 if ( temp_edx >= p . p1 ) {
 temp_edx = p . p1 ;
 loc_eax ++ ;
 p . p2 += temp_edx ;
 }
 if ( ( ( p . p1 ) & 0xff000000 ) == 0 ) {
 p . p2 <<= 8 ;
 p . p1 <<= 8 ;
 p . p0 ++ ;
 }
 }
 while ( -- loc_ecx ) ;
 loc_ecx = ( loc_ecx & 0xffffff00 ) | 4 ;
 loc_eax <<= 4 ;
 loc_ebp += loc_eax ;
 loc_edx = loc_ebx + 0x18 ;
 }
 loc_eax = 1 ;
 loc_eax <<= ( loc_ecx & 0xff ) ;
 loc_ebp8 = loc_edx ;
 temp_ebp = loc_ecx ;
 loc_ecx = loc_eax ;
 loc_eax = temp_ebp ;
 if ( lzma_upack_esi_50 ( & p , 1 , loc_ecx , & loc_edx , loc_ebp8 , & loc_eax , bs , bl ) == 0xffffffff ) return - 1 ;
 loc_ecx = temp_ebp ;
 temp_ebp = CLI_SRS ( ( int32_t ) loc_eax , 31 ) ;
 do {
 temp_ebp += temp_ebp ;
 temp_ebp += ( loc_eax & 1 ) ;
 loc_eax >>= 1 ;
 }
 while ( -- loc_ecx ) ;
 loc_ebp += temp_ebp ;
 }
 loc_ebp ++ ;
 loc_ecx = jakas_kopia ;
 }
 else {
 loc_edx += loc_ecx ;
 if ( ( ret = lzma_upack_esi_00 ( & p , loc_edx , bs , bl ) ) ) {
 loc_edx += 0x60 ;
 if ( ( ret = lzma_upack_esi_00 ( & p , loc_edx , bs , bl ) ) ) {
 loc_edx += loc_ecx ;
 ret = lzma_upack_esi_00 ( & p , loc_edx , bs , bl ) ;
 temp_ebp = loc_ebp ;
 loc_ebp = state [ 4 ] ;
 state [ 4 ] = state [ 3 ] ;
 state [ 3 ] = temp_ebp ;
 if ( ret ) {
 temp_ebp = loc_ebp ;
 loc_ebp = state [ 5 ] ;
 state [ 5 ] = temp_ebp ;
 }
 }
 else {
 temp_ebp = loc_ebp ;
 loc_ebp = state [ 3 ] ;
 state [ 3 ] = temp_ebp ;
 }
 }
 else {
 loc_edx += loc_ecx ;
 if ( ( ret = lzma_upack_esi_00 ( & p , loc_edx , bs , bl ) ) ) {
 }
 else {
 loc_eax |= 1 ;
 eax_copy = loc_eax ;
 edi_copy = loc_edi ;
 edi_copy -= state [ 2 ] ;
 loc_ecx = ( loc_ecx & 0xffffff00 ) | 0x80 ;
 if ( ! CLI_ISCONTAINED ( bs , bl , edi_copy , 1 ) || ! CLI_ISCONTAINED ( bs , bl , loc_edi , 1 ) ) return - 1 ;
 loc_al = ( * ( uint8_t * ) edi_copy ) & 0xff ;
 * loc_edi ++ = loc_al ;
 continue ;
 }
 }
 eax_copy = loc_eax ;
 loc_edx = loc_ebx + 0x778 ;
 if ( lzma_upack_esi_54 ( & p , loc_eax , & loc_ecx , & loc_edx , & temp , bs , bl ) == 0xffffffff ) return - 1 ;
 loc_eax = loc_ecx ;
 loc_ecx = temp ;
 }
 if ( ! CLI_ISCONTAINED ( bs , bl , loc_edi , loc_ecx ) || ! CLI_ISCONTAINED ( bs , bl , loc_edi - loc_ebp , loc_ecx + 1 ) ) return - 1 ;
 state [ 2 ] = loc_ebp ;
 for ( i = 0 ;
 i < loc_ecx ;
 i ++ , loc_edi ++ ) * loc_edi = * ( loc_edi - loc_ebp ) ;
 loc_eax = ( loc_eax & 0xffffff00 ) | * ( uint8_t * ) ( loc_edi - loc_ebp ) ;
 loc_ecx = 0x80 ;
 }
 else {
 do {
 if ( ( loc_al = ( loc_eax & 0xff ) ) + 0xfd > 0xff ) loc_al -= 3 ;
 else loc_al = 0 ;
 loc_eax = ( loc_eax & 0xffffff00 ) | loc_al ;
 }
 while ( loc_al >= 7 ) ;
 eax_copy = loc_eax ;
 if ( loc_edi > init_edi && loc_edi < bl + bs ) {
 loc_ebp = ( * ( uint8_t * ) ( loc_edi - 1 ) ) >> shlsize ;
 }
 else {
 loc_ebp = 0 ;
 }
 loc_ebp *= ( int ) 0x300 ;
 loc_ebp8 = loc_ebx + ( ( loc_ebp << 2 ) + 0x1008 ) ;
 edi_copy = loc_edi ;
 loc_eax = ( loc_eax & 0xffffff00 ) | 1 ;
 if ( loc_ecx ) {
 uint8_t loc_cl = loc_ecx & 0xff ;
 loc_edi -= state [ 2 ] ;
 if ( ! CLI_ISCONTAINED ( bs , bl , loc_edi , 1 ) ) return - 1 ;
 do {
 loc_eax = ( loc_eax & 0xffff00ff ) | ( ( * loc_edi & loc_cl ) ? 0x200 : 0x100 ) ;
 loc_edx = loc_ebp8 + ( loc_eax << 2 ) ;
 ret = lzma_upack_esi_00 ( & p , loc_edx , bs , bl ) ;
 loc_al = loc_eax & 0xff ;
 loc_al += loc_al ;
 loc_al += ret ;
 loc_al &= 0xff ;
 loc_eax = ( loc_eax & 0xffffff00 ) | loc_al ;
 loc_cl >>= 1 ;
 if ( loc_cl ) {
 uint8_t loc_ah = ( loc_eax >> 8 ) & 0xff ;
 loc_ah -= loc_al ;
 loc_ah &= 1 ;
 if ( ! loc_ah ) {
 loc_eax = ( loc_eax & 0xffff0000 ) | ( loc_ah << 8 ) | loc_al ;
 if ( lzma_upack_esi_50 ( & p , loc_eax , 0x100 , & loc_edx , loc_ebp8 , & loc_eax , bs , bl ) == 0xffffffff ) return - 1 ;
 break ;
 }
 }
 else break ;
 }
 while ( 1 ) ;
 }
 else {
 loc_ecx = ( loc_ecx & 0xffff00ff ) | 0x100 ;
 if ( lzma_upack_esi_50 ( & p , loc_eax , loc_ecx , & loc_edx , loc_ebp8 , & loc_eax , bs , bl ) == 0xffffffff ) return - 1 ;
 }
 loc_ecx = 0 ;
 loc_edi = edi_copy ;
 }
 if ( ! CLI_ISCONTAINED ( bs , bl , loc_edi , 1 ) ) return - 1 ;
 * loc_edi ++ = ( loc_eax & 0xff ) ;
 }
 while ( loc_edi < end_edi ) ;
 return 1 ;
 }