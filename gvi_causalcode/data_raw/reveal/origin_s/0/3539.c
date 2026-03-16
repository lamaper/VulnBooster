static int freev ( struct vars * v , int err ) {
 if ( v -> re != NULL ) rfree ( v -> re ) ;
 if ( v -> subs != v -> sub10 ) FREE ( v -> subs ) ;
 if ( v -> nfa != NULL ) freenfa ( v -> nfa ) ;
 if ( v -> tree != NULL ) freesubre ( v , v -> tree ) ;
 if ( v -> treechain != NULL ) cleanst ( v ) ;
 if ( v -> cv != NULL ) freecvec ( v -> cv ) ;
 if ( v -> cv2 != NULL ) freecvec ( v -> cv2 ) ;
 if ( v -> lacons != NULL ) freelacons ( v -> lacons , v -> nlacons ) ;
 ERR ( err ) ;
 return v -> err ;
 }