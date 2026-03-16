static bool riccb_needed(void *opaque)

{


    if (kvm_enabled()) {

        return kvm_s390_get_ri();

    }


    return 0;

}
