#Concepts & Configuration Files

The bootloader is in the MBR for the whole or a part. This way, the BIOS can find the bootloader. Part of the bootloader can live on a partition. With grub this is usually in */boot*. [source](http://askubuntu.com/a/142922)

So in short, the boot process is:
1. Box is powered on
2. BIOS looks for a bootable device via either UEFI or searching for a MBR
3. MBR has data on the boot loader. Once the boot loader is found, the system passes control to the boot loader.
4. The boot loader presents a menu of kernel options to boot to if multiple kernels are found (you an configure a default to boot into)
5. The boot loader loads the kernel into memory
6. The boot loader gives control to the kernel and passes on some config
7. Kernel starts all hardware modules and initializes all hardwire it can find (it gets the data from initramfs)and runs init on our system, this is the pid 1 and can be systemd
8. Initramfs version of systemd will move into the initrd.target which will mount filesystems
9. The kernel root file system is then switched from initramfs to the root file system /
10. Systemd takes over and the default target as specified is called

[This article](https://neosmart.net/wiki/mbr-boot-process/#The_BootDevice) describes into more techinal detail how the boot process works and makes a disctintion between first-stage bootloader and second-stage bootloader with the partition bootsector

Most distro's will install GRUB2 automatically during the installation boot process.

##Best method for restoring an info

`grub2-mkconfig > /boot/grub/grub.cfg`

#grub2-install and grub2-mkconfig

*Sometimes grub2 is installed in */boot/grub* and sometimes in */boot/grub2*

With the lab server you cannot exercise the boot process. Use a VM for that.

1. Config file */boot/grub/menu.lst* is replaced with */boot/grub/grub.cfg*. We use a tool to build this config file based on the */etc/* dir
2. Custom menu items can be created in /etc/grub.d/40_custom/
3. */etc/default/grub* contains default setting for grub. It looks like:

```
GRUB_TIMEOUT=1
GRUB_DISTRIBUTOR="$(sed 's, release .*$,,g' /etc/system-release)"
GRUB_DEFAULT=saved
GRUB_DISABLE_SUBMENU=true
GRUB_TERMINAL="serial console"
GRUB_SERIAL_COMMAND="serial --speed=115200"
GRUB_CMDLINE_LINUX="console=ttyS0,115200 console=tty0 vconsole.font=latarcyrheb-sun16 crashkernel=auto  vconsole.keymap=us"
GRUB_DISABLE_RECOVERY="true"
```

So to make the config file, enter `grub2-mkconfig > `grub2-mkconfig > /boot/grub2/grub.cfg`

##install GRUB2

To install grub: `grub-install /dev/device` or `grub2-install /dev/device`. Note that this must have MBR, so on GPT drive this doesn't work.

#GRUB2 and GRUB Legacy Configuration Files

To clear it up:

1. Grub.cfg is the name of the GRUB2 config files generally found in /boot/grub/grub.cfg, but in RedHat is it in /boot/grub2/grub.cfg
2. */etc/grub.conf* is a GRUB legacy config file and is a symlink to */boot/grub2/grub.cfg (it is legacy because now we use `grub2-mkconfig`)
3. */etc/grub2.cfg* is a symlink to */boot/grup2/grub.cfg
4. */boot/grub/menu.lst is also a GRUB legacy config file

#initramfs and /boot

*/boot is part of FHS and contains config files relating to booting. Examples:

1. grub config
2. initramfs config
3. kernel image config

Initramsfs is a gzipped cpio archive that contains the kernel modules required for all hardware needed for the system boot. After the boot loader hands of the boot process to the kernel, the kernel wil load and initialize the hardwrire required for the system. The info and drivers for this is founded by the kernel in initramfs.

After the init scripts and the hardware drivers are loaded, the system can then mount on */* whatever is stated in *etc/fstab*
