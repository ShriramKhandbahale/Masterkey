#!/bin/bash       

wget -q --spider http://google.com

if [ $? -eq 0 ]; then
    
    echo "Processing your request, plese wait..."
    python3 ../.mail/sendOtp 
    clear
    echo "We have sent a verification code to $(cat ../.mail/.mail.txt)"
 
fi
