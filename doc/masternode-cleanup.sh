#/bin/bash

# Check if is root
if [ "$(whoami)" != "root" ]; then
  echo "Script must be run as user: root"
  exit -1
fi

echo && echo "Stopping chipo"
chipo-cli stop

echo && echo "moving chipo executables to another directory"
mv /usr/bin/chipod /usr/local/bin/chipod
mv /usr/bin/chipo-tx /usr/local/bin/chipo-tx
mv /usr/bin/chipo-cli /usr/local/bin/chipo-cli

echo && echo "starting chipod"
chipod