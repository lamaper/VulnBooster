void SFDefaultOS2SubSuper ( struct pfminfo * pfminfo , int emsize , double italic_angle ) {
 double s = sin ( italic_angle * 3.1415926535897932 / 180.0 ) ;
 pfminfo -> os2_supysize = pfminfo -> os2_subysize = .7 * emsize ;
 pfminfo -> os2_supxsize = pfminfo -> os2_subxsize = .65 * emsize ;
 pfminfo -> os2_subyoff = .14 * emsize ;
 pfminfo -> os2_supyoff = .48 * emsize ;
 pfminfo -> os2_supxoff = s * pfminfo -> os2_supyoff ;
 pfminfo -> os2_subxoff = - s * pfminfo -> os2_subyoff ;
 pfminfo -> os2_strikeysize = 102 * emsize / 2048 ;
 pfminfo -> os2_strikeypos = 530 * emsize / 2048 ;
 }