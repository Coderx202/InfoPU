# InfoPU
a Simple tool to display your system info for almost all Linux Distros.


## Features

- CPU info
- Memory info
- BIOS/UEFI info
- Operating system details (Kernel, etc..)
- Motherboard info
- System Vendor
- Product name (Laptop name for example)
- Shows current package manager

## Update patches/added
- You can now see your package manager (dnf, apt, etc....)
- Fixed a Bug in the CheckSecureBoot() function which would bug out if the user didn't have mokutil
- Now returns "N/A" if the required info is not found (for example in VM's and Containers it would bug out)

## Usage

Clone the repository and run these commands:

<pre lang="markdown">git clone https://github.com/Coderx202/InfoPU.git
cd InfoPU
g++ -o infopu InfoPU.cpp
./infopu
</pre>
## Tested distros
- Fedora
- Arch
- Debian (And most Debian based one for example ubuntu. etc...)
- OpenSUSE Tumbleweed

