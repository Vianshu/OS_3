mkdir Kerne3F
cd Kerne3F
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.0.9.tar.xz
unxz linux-6.0.9.tar.xz
tar -xvf linux-6.0.9.tar
cd linux-6.0.9
make mrproper
wget -O config https://raw.githubusercontent.com/gopi487krishna/ArtixConfig/main/config-rev-9-gold
make
