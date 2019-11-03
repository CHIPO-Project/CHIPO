#!/bin/bash

now=$(date +"%m_%d_%Y")



# Check if is root
if [ "$(whoami)" != "root" ]; then
  echo "Script must be run as user: root"
  exit -1
fi

apt install unzip

echo && echo "going to root directory"
cd ~/

echo && echo "Stopping daemon..."
chipo-cli stop

echo && echo "downloading update"
wget https://github.com/amusedbnet/CHIPO/releases/download/v1.2.0/chipo-linux-ubuntu1604-v1.2.0.zip -O chipo-v1.2.0.zip

mkdir chipobackup
cd chipobackup
mkdir $now

backuppath=~/chipobackup/$now

echo && echo "backing up wallet.dat masternode.conf chipo.conf to ${backuppath}"
cd ../.chipo
cp wallet.dat $backuppath
cp masternode.conf $backuppath
cp chipo.conf $backuppath

cd ~/

echo && echo "unzipping daemons"
unzip chipo-v1.1.0.zip -d ~/chipo-release
cd chipo-release
chmod +x chipod
chmod +x chipo-cli
chmod +x chipo-tx
chmod +x chipo-qt

echo && echo "moving to /usr/bin"
sudo mv chipo-cli /usr/local/bin/chipo-cli
sudo mv chipo-tx /usr/local/bin/chipo-tx
sudo mv chipod /usr/local/bin/chipod

echo && echo "cleaning up"
cd ~/
rm chipo-release -rf
rm chipo-v1.2.0.zip

echo && echo "starting daemon"
chipod
