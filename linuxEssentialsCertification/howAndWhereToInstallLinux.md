#Using the Linux Essentials Lab Server#

The Linux Essentials Server is a CentOS7 distribution

##Change password & become root##

Start by changing the password `passwd`
Do this for root as wel, become root: `sudo -`

##Setup VNC##
* `cat ~/VNCHOWTO`
* Reboot: `su -` `reboot`

##Install Linux on VirtualBox##
* Best practice: do a `yum upgrade` after installation

###Guest Utility Packages###
Up the performance of a virtual machine. Example: mouse behaviour is more intuitive. To install: 

* `yum install kernel-dev`
* `yum install gcc*`
* In the VirtualBox Menu Devices->Insert Guest Additions Images
