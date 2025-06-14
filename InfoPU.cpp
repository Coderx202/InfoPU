#include <fstream>
#include <string>
#include <iostream>


class CPUInfo{
public:
std::string getCPUName()   {return readline("/proc/cpuinfo", "model name");   }
std::string getCPUCores()  {return readline("/proc/cpuinfo", "cpu cores");    }
std::string getCPUVendor() {return readline("/proc/cpuinfo", "vendor_id");    }

private:

std::string readline(const std::string& path, const std::string& word) {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(word) != std::string::npos) {
            return line.substr(line.find(":") + 2);
        }
    }

    return "N/A"; 
}

};


class BIOSInfo {
public:
    std::string getBIOSVendor()     { return read("/sys/class/dmi/id/bios_vendor");  }
    std::string getBIOSVersion()    { return read("/sys/class/dmi/id/bios_version"); }
    std::string getBIOSDate()       { return read("/sys/class/dmi/id/bios_date");    }
    std::string getBIOSRelease()    { return read("/sys/class/dmi/id/bios_release");    }
    
private:
    std::string read(const std::string& path) {
        std::ifstream file(path);
        std::string line;
        if (file && std::getline(file, line)) {
            return line;
        }
        return "N/A";
    }
};



class MotherboardInfo{
public:
	std::string getMotherboardName() {return read("/sys/class/dmi/id/board_name");}
	std::string getMotherboardVendor() {return read("/sys/class/dmi/id/board_vendor");}
	std::string getSystemVendor() {return read("/sys/class/dmi/id/sys_vendor");}
private:
    std::string read(const std::string& path) {
        std::ifstream file(path);
        std::string line;
        if (file && std::getline(file, line)) {
            return line;
        }
        return "N/A";
    }

};


void meminfo(){
    std::ifstream file("/proc/meminfo");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("MemTotal") != std::string::npos) {
            std::cout << "Total RAM: " << line.substr(line.find(":") + 8) << std::endl;
            break;
        }
    }
}

void CheckSecureBoot(){
    int ret = system("mokutil --sb-state | grep -q 'SecureBoot enabled'");

    if(ret == 0){
        std::cout << "Secure Boot: Enabled\n";
    }
    else {
        std::cout << "Secure boot: Disabled\n";
    }


}



std::string getProductName(){

	std::ifstream file("/sys/class/dmi/id/product_name");
	std::string line;

    std::getline(file, line);
    return line;

}

std::string getKernelInfo(){
    std::ifstream file("/proc/sys/kernel/osrelease");
    std::string line;
    std::getline(file, line);
    return line;
}


std::string shell(){

    system("ps -p $$ -o comm= > shell.txt");

    std::ifstream file("shell.txt");
    std::string line;
    std::getline(file, line);
    std::remove("shell.txt");
    return line;
}

// TODO: Make this function get the packmanager in use (do not use a 100 system(); calls with "which" to see if a packmanager exists)

void getPackageManager(){}


std::string BuildInfo(){
    std::ifstream build("/proc/version");
    std::string line;
    
    std::getline(build, line);
    return line;
}


int main(){

    BIOSInfo bios;
    MotherboardInfo Motherboard;
    CPUInfo CPU;


    std::cout << "CPU Model: " << CPU.getCPUName() << "\n";
    std::cout << "CPU Cores: " << CPU.getCPUCores() << "\n";
    std::cout << "CPU Vendor: " << CPU.getCPUVendor() << "\n";
    meminfo();
    CheckSecureBoot();
    std::cout << "BIOS/UEFI Vendor: " << bios.getBIOSVendor() << "\n";
    std::cout << "BIOS/UEFI Version: " << bios.getBIOSVersion() << "\n";
    std::cout << "BIOS/UEFI Date: " << bios.getBIOSDate() << "\n";
    std::cout << "BIOS/UEFI Release: " << bios.getBIOSRelease() << "\n";
    std::cout << "Motherboard Name: " << Motherboard.getMotherboardName() << "\n";
    std::cout << "Motherboard Vendor: " << Motherboard.getMotherboardVendor() << "\n";
    std::cout << "System Vendor: " << Motherboard.getSystemVendor() << "\n";
    std::cout << "Product Name: " << getProductName() << "\n";
    std::cout << "Kernel: " << getKernelInfo() << "\n";
    std::cout << "Default Shell: " << shell() << "\n";
    std::cout << "Build Info: " << BuildInfo() << "\n";
}