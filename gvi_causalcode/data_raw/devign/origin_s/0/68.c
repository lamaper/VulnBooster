static inline bool vhost_needs_vring_endian(VirtIODevice *vdev)

{

    if (virtio_vdev_has_feature(vdev, VIRTIO_F_VERSION_1)) {

        return false;

    }



    return !virtio_is_big_endian(vdev);


    return virtio_is_big_endian(vdev);



    return false;


}
