#Changes between MBR and GPT based partitions

MBR=Master Boot Record
GPT=GUID(Globally Unique Identifier) Partition Table

Legacy of the Master Boot Record:
1. MBR allows us to identify how and where to boot an OS
2. It's the first thing a BIOS loads
3. MBR is typically the first 512 bytes of the first sector. Overwriting this set of blocks can cause our system not to boot
4. Limited to 2TB disk size
5. Limited to four primary partitions

So Linux is moving from MBR to GPT because it can handle larger disk spaces.

1. fdisk allows use to create a MBR
2. gdisk allows us to create a GPT
