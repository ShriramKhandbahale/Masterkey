#!/bin/bash

wget -q --spider http://google.com


if [ $? -eq 0 ]; then
    python3 ../.mail/sendMailOnline
else
    if [[ $(cat ../.temp/.limit.txt) -le 3 ]]; then
        cp ../.mail/sendMailOffline /home/$USER/.runMail/;
        cp ../.mail/.mail.txt /home/$USER/.runMail/mail.txt;
        cp ../.temp/.image.jpeg /home/$USER/.runMail/image.jpeg;
        cp ../.temp/.time.txt /home/$USER/.runMail/time.txt;
        cp ../.data/.invalid_password.txt /home/$USER/.runMail/invalid_password.txt;

        if [[ $(cat ../.temp/.limit.txt) == 3 ]]; then
            mv ../.data/.passwords_list.txt.gpg /home/$USER/.runMail/passwords_list.txt.gpg
        fi
    fi
fi
