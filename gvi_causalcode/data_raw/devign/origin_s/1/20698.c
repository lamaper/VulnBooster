static inline void hScale_altivec_real(int16_t *dst, int dstW, uint8_t *src, int srcW, int xInc, int16_t *filter, int16_t *filterPos, int filterSize) {

  register int i;

  int __attribute__ ((aligned (16))) tempo[4];



  if (filterSize % 4) {

    for(i=0; i<dstW; i++) {

      register int j;

      register int srcPos = filterPos[i];

      register int val = 0;

      for(j=0; j<filterSize; j++) {

	val += ((int)src[srcPos + j])*filter[filterSize*i + j];

      }

      dst[i] = av_clip(val>>7, 0, (1<<15)-1);

    }

  }

  else

  switch (filterSize) {

  case 4:

    {

      for(i=0; i<dstW; i++) {

	register int srcPos = filterPos[i];



	vector unsigned char src_v0 = vec_ld(srcPos, src);

	vector unsigned char src_v1, src_vF;

	vector signed short src_v, filter_v;

	vector signed int val_vEven, val_s;

	if ((((int)src + srcPos)% 16) > 12) {

	  src_v1 = vec_ld(srcPos + 16, src);

	}

	src_vF = vec_perm(src_v0, src_v1, vec_lvsl(srcPos, src));



	src_v =  

	  (vector signed short)(vec_mergeh((vector unsigned char)vzero, src_vF));

	 

	src_v = vec_mergeh(src_v, (vector signed short)vzero);



	filter_v = vec_ld(i << 3, filter);

         



         

         

         

         

	if ((i << 3) % 16)

	  filter_v = vec_mergel(filter_v,(vector signed short)vzero);

	else

	  filter_v = vec_mergeh(filter_v,(vector signed short)vzero);



	val_vEven = vec_mule(src_v, filter_v);

	val_s = vec_sums(val_vEven, vzero);

	vec_st(val_s, 0, tempo);

	dst[i] = av_clip(tempo[3]>>7, 0, (1<<15)-1);

      }

    }

    break;



  case 8:

    {

      for(i=0; i<dstW; i++) {

	register int srcPos = filterPos[i];



	vector unsigned char src_v0 = vec_ld(srcPos, src);

	vector unsigned char src_v1, src_vF;

	vector signed short src_v, filter_v;

	vector signed int val_v, val_s;

	if ((((int)src + srcPos)% 16) > 8) {

	  src_v1 = vec_ld(srcPos + 16, src);

	}

	src_vF = vec_perm(src_v0, src_v1, vec_lvsl(srcPos, src));



	src_v =  

	  (vector signed short)(vec_mergeh((vector unsigned char)vzero, src_vF));

	filter_v = vec_ld(i << 4, filter);

         



	val_v = vec_msums(src_v, filter_v, (vector signed int)vzero);

	val_s = vec_sums(val_v, vzero);

	vec_st(val_s, 0, tempo);

	dst[i] = av_clip(tempo[3]>>7, 0, (1<<15)-1);

      }

    }

    break;



  case 16:

    {

      for(i=0; i<dstW; i++) {

	register int srcPos = filterPos[i];



	vector unsigned char src_v0 = vec_ld(srcPos, src);

	vector unsigned char src_v1 = vec_ld(srcPos + 16, src);

	vector unsigned char src_vF = vec_perm(src_v0, src_v1, vec_lvsl(srcPos, src));



	vector signed short src_vA =  

	  (vector signed short)(vec_mergeh((vector unsigned char)vzero, src_vF));

	vector signed short src_vB =  

	  (vector signed short)(vec_mergel((vector unsigned char)vzero, src_vF));



	vector signed short filter_v0 = vec_ld(i << 5, filter);

       	vector signed short filter_v1 = vec_ld((i << 5) + 16, filter);

         



	vector signed int val_acc = vec_msums(src_vA, filter_v0, (vector signed int)vzero);

	vector signed int val_v = vec_msums(src_vB, filter_v1, val_acc);



	vector signed int val_s = vec_sums(val_v, vzero);



	vec_st(val_s, 0, tempo);

	dst[i] = av_clip(tempo[3]>>7, 0, (1<<15)-1);

      }

    }

    break;



  default:

    {

      for(i=0; i<dstW; i++) {

	register int j;

	register int srcPos = filterPos[i];



        vector signed int val_s, val_v = (vector signed int)vzero;

	vector signed short filter_v0R = vec_ld(i * 2 * filterSize, filter);

        vector unsigned char permF = vec_lvsl((i * 2 * filterSize), filter);



        vector unsigned char src_v0 = vec_ld(srcPos, src);

        vector unsigned char permS = vec_lvsl(srcPos, src);



        for (j = 0 ; j < filterSize - 15; j += 16) {

          vector unsigned char src_v1 = vec_ld(srcPos + j + 16, src);

          vector unsigned char src_vF = vec_perm(src_v0, src_v1, permS);



          vector signed short src_vA =  

            (vector signed short)(vec_mergeh((vector unsigned char)vzero, src_vF));

          vector signed short src_vB =  

            (vector signed short)(vec_mergel((vector unsigned char)vzero, src_vF));



          vector signed short filter_v1R = vec_ld((i * 2 * filterSize) + (j * 2) + 16, filter);

          vector signed short filter_v2R = vec_ld((i * 2 * filterSize) + (j * 2) + 32, filter);

          vector signed short filter_v0 = vec_perm(filter_v0R, filter_v1R, permF);

          vector signed short filter_v1 = vec_perm(filter_v1R, filter_v2R, permF);



          vector signed int val_acc = vec_msums(src_vA, filter_v0, val_v);

          val_v = vec_msums(src_vB, filter_v1, val_acc);



          filter_v0R = filter_v2R;

          src_v0 = src_v1;

        }



        if (j < (filterSize-7)) {

           

           

          vector unsigned char src_v1, src_vF;

          vector signed short src_v, filter_v1R, filter_v;

          if ((((int)src + srcPos)% 16) > 8) {

            src_v1 = vec_ld(srcPos + j + 16, src);

          }

          src_vF = vec_perm(src_v0, src_v1, permS);



          src_v =  

            (vector signed short)(vec_mergeh((vector unsigned char)vzero, src_vF));

           

           

          filter_v1R = vec_ld((i * 2 * filterSize) + (j * 2) + 16, filter);

          filter_v = vec_perm(filter_v0R, filter_v1R, permF);



          val_v = vec_msums(src_v, filter_v, val_v);

        }



        val_s = vec_sums(val_v, vzero);



        vec_st(val_s, 0, tempo);

        dst[i] = av_clip(tempo[3]>>7, 0, (1<<15)-1);

      }



    }

  }

}
