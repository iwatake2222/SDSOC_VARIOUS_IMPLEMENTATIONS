# SDSoC various implementations
I implemented a variety of ways on SDSoC.

## Environment
- Target Board: ZYBO (Z7-20)
- Host PC: Windows 10 64-bit
	- SDx 2018.2

## SDSoC Platform
SDSoC Platform is included: `design_1`

## How To Build
- Open SDx
	- File -> Switch Workspace
	- Select SDSOC_VARIOUS_IMPLEMENTATIONS folder (including `design_1` and `test_myip`)
- Right click on Project Explorer -> Import
	- General -> Existing Projects into Workspace
	- Sselect `design_1` and `test_myip`
- design_1 -> platform.spr
	- Add to Custom Repositories
- test_myip -> project.sdx
	- Platform
		- Select design_1
	- Hardware Functions
		- Add any function which you want
- Build
- Upload files to SD on ZYBO(`root@192.168.1.87:/run/media/mmcblk0p1/`)
	- `test_myip/Release/sd_card/*`
- Reboot ZYBO

