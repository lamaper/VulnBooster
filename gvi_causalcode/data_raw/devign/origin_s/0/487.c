void check_values (eq2_param_t *par)

{

   



  if ((par->c == 1.0) && (par->b == 0.0) && (par->g == 1.0)) {

    par->adjust = NULL;

  }


  else if (par->g == 1.0 && ff_gCpuCaps.hasMMX) {

    par->adjust = &affine_1d_MMX;

  }


  else {

    par->adjust = &apply_lut;

  }

}
