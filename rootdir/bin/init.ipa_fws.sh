#!/vendor/bin/sh

DEVICE=`getprop ro.boot.bootloader | cut -c5`
CURRENT_BOOTLOADER_DATE=`getprop ro.boot.bootloader | cut -c9`

case "$DEVICE" in
    "B")
        setprop ro.vendor.device.variant "b"
        ;;
    "N")
        setprop ro.vendor.device.variant "n"
        ;;
esac

if [ "$CURRENT_BOOTLOADER_DATE" -eq 1 ]; then
    # bootloader revision 1
    setprop ro.vendor.ipa.ver "1"
elif [ "$CURRENT_BOOTLOADER_DATE" -eq 2 ]; then
    # bootloader revision 2
    setprop ro.vendor.ipa.ver "2"
else
    # bootloader revision 3
    setprop ro.vendor.ipa.ver "3"
fi
