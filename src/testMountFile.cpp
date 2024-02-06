#include <iostream>
#include <cstring>
#include <sys/mount.h>

using namespace std;

int status;

#define MOUNT_PATH "/dev/loop8"

int main(){
    
    status = mount(MOUNT_PATH, "/media/usb0", "vfat", MS_NOATIME, NULL);
    cout << "mount status " << std::strerror(errno) << endl;

    status = umount("/media/usb0");
    cout << "umount status" << errno << endl;

    return 0;
}