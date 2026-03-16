static int kvm_put_xcrs(CPUState *env)

{


    struct kvm_xcrs xcrs;



    if (!kvm_has_xcrs())

        return 0;



    xcrs.nr_xcrs = 1;

    xcrs.flags = 0;

    xcrs.xcrs[0].xcr = 0;

    xcrs.xcrs[0].value = env->xcr0;

    return kvm_vcpu_ioctl(env, KVM_SET_XCRS, &xcrs);


    return 0;


}
