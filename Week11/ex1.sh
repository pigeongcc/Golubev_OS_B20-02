# create a file of 100 MB size
fallocate -l $((100*1024*1024)) lofs.img
du -sh lofs.img # check the size of the file

# set a loopback device on the created file
sudo losetup -fP lofs.img
sudo losetup -a # check the generated loop device


#sudo losetup -a | sed -n '2 p'

# create a filesystem for the loopback device
sudo mkfs.ext4 lofs.img

# create a directory
mkdir lofsdisk

# mount the created filesystem on the mount point lofsdisk

sudo mount -o loop lofs.img lofsdisk
df -hP lofsdisk/ # check size of the new mount point
