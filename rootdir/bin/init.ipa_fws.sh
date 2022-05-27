#!/vendor/bin/sh

DEVICE=`getprop ro.boot.bootloader | cut -c5`

case "$DEVICE" in
    "B")
        setprop ro.vendor.device.variant "b"
        ;;
    "N")
        setprop ro.vendor.device.variant "n"
        ;;
esac
