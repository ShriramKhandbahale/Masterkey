#! /bin/bash

if [[ $(which feh) != "" && $(which streamer) != "" ]]; then
    echo All packages Installed Successfully;
else
    clear;
    echo "Error: Unable to install packages";
    echo "Please check your internet connection or try again later.";
    sleep 5;
    exit 1;
fi;

#adding runmail in if-up.d for executing the script with python3
{
  echo "#! /bin/bash"
  echo
  echo "python3 /home/$USER/.runMail/sendMailOffline"
} &> runMail

chmod +x runMail
sudo mv runMail /etc/network/if-up.d/	

mkdir /home/$USER/.runMail

printf $USER > .username.txt
sudo mv .username.txt /etc/network/if-up.d/
