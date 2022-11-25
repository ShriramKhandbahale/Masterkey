#! bin/bash

main(){
	cd /home/$USER/Documents/.Program-Files/.MasterKey/.main/ 
	wget https://github.com/TheSudoersClub/Masterkey/blob/main/MasterKey.c?raw=true

	clear
	
	pleaseWaitAnimation

	if [[ -f "MasterKey.c?raw=true" ]]; then
		
		diff -qw MasterKey.c?raw=true .masterkey.c > /home/$USER/Documents/.Program-Files/.MasterKey/.temp/.message.txt
		message=$(cat /home/$USER/Documents/.Program-Files/.MasterKey/.temp/.message.txt)

		if [[ $message == "Files MasterKey.c?raw=true and .masterkey.c differ" ]]; then
			clear
			echo "There are updates available"
			read -p 'Do you want to install the updates [Y/n] : ' choice
			echo

			if [[ $choice == "Y" || $choice == "y" ]]; then
				clear
				echo "Updating [>                    ]    0%"
				sleep 0.5
				clear

				echo "Updating [==>                  ]    10%"
				sleep 0.5
				clear

				echo "Updating [====>                ]    20%"
				sleep 0.5
				clear

				echo "Updating [======>              ]    30%"
				sleep 0.5
				clear

				echo "Updating [========>            ]    40%"
				sleep 0.5
				clear

				echo "Updating [==========>          ]    50%"
				sleep 0.5
				clear

				echo "Updating [============>        ]    60%"
				sleep 0.5
				clear

				echo "Updating [==============>      ]    70%"
				sleep 0.5
				clear

				echo "Updating [================>    ]    80%"
				sleep 0.5
				clear

				echo "Updating [==================>  ]    90%"
				sleep 0.5
				clear

				echo "Updating [====================>]   100%"
				sleep 1
				clear

				rm .masterkey.c -f
				mv MasterKey.c?raw=true .masterkey.c

				rm .masterkey.out -f
				gcc .masterkey.c -o .masterkey.out

				clear
				echo app successfully updated.

				sleep 1
				pkill terminal
			else
				rm MasterKey.c?raw=true
			fi

		else
			clear
			echo "The app is upto date"
			echo
			rm MasterKey.c?raw=true
		fi
		
	else
		clear
		echo "Error: unable to check for updates"
		echo "Please check your internet connection or try again later."
		echo
	fi
}



pleaseWait(){
    echo "Checking for updates"
    sleep 0.25
    clear

    echo "Checking for updates."
    sleep 0.25
    clear

    echo "Checking for updates.."
    sleep 0.25
    clear

    echo "Checking for updates..."
    sleep 0.25
    clear

    echo "Checking for updates .."
    sleep 0.25
    clear

    echo "Checking for updates  ."
    sleep 0.25
    clear
}

pleaseWaitAnimation(){
	pleaseWait
	pleaseWait
	pleaseWait
	pleaseWait
	pleaseWait
	pleaseWait
	pleaseWait
	pleaseWait
}

main "$@"; exit
