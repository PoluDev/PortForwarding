# Port forwarding
-  **port forwarding or port mapping is an application of network address translation.**  
  
![Port Forwarding](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5f/NAPT-en.svg/400px-NAPT-en.svg.png)


## How does it work?
This work Well.

## Features
- Installed cmake
- Installed Boost
- Installed QT createor 5.14.
- And so on ...

## Requirements
- Any Linux machine...

## Initial Configuration Guide

+ **Download And Install Qt From below Link**
   * [Download QT.](https://download.qt.io/archive/qt/5.14/5.14.0/)  
+  **Building and Installing cmake (Recommended for developers)**
   * For this approach you need to install the GCC tools:  
  `sudo apt update`  
  `sudo apt install build-essential libtool autoconf unzip wget`  
   * Uninstall the default version provided by Ubuntu's package manager as in  
   `sudo apt remove --purge --auto-remove cmake`  
   * Go to the [official CMake webpage](https://cmake.org/download/), then download and extract the latest version. Update the version and build variables in the following command to get the desired version:  
    `version=3.24`  
    `build=1`  
    `## don't modify from here`  
    `mkdir ~/temp`  
    `cd ~/temp`  
    `wget https://cmake.org/files/v$version/cmake-$version.$build.tar.gz`  
    `tar -xzvf cmake-$version.$build.tar.gz`  
    `cd cmake-$version.$build/`  
    * Install the extracted source by running:  
    `./bootstrap`  
    `make -j$(nproc)`  
    `sudo make install`  
    * Test your new cmake version.  
    `$ cmake --version`  
    * Results of cmake --version:  
    `cmake version 3.24.X`  
    `CMake suite maintained and supported by Kitware(kitware.com/cmake).`  
+ **Install boost**  
    `sudo apt-get install libboost-all-dev`  



# How to open Project
1. Clone it from : https://github.com/PoluDev/PortForwarding.git
1. Change The Branch by this Code "git checkout Log" 
2. open Project by Qt Creator, (open file with txt postfix)
3. Build Project

## Usage
 **Port forwarding allows remote computers (for example, computers on the Internet) to connect to a specific computer or service within a private local-area network (LAN)**  
 
## Author
 Ehsan Panahi

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://user-images.githubusercontent.com/25423296/163456776-7f95b81a-f1ed-45f7-b7ab-8fa810d529fa.png">
  <source media="(prefers-color-scheme: light)" srcset="https://user-images.githubusercontent.com/25423296/163456779-a8556205-d0a5-45e2-ac17-42d089e3c3f8.png">
  <img alt="Shows an illustrated sun in light mode and a moon with stars in dark mode." src="https://user-images.githubusercontent.com/25423296/163456779-a8556205-d0a5-45e2-ac17-42d089e3c3f8.png">
</picture>



