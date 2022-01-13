if [ -z $1 ]; then
	echo "ERROR : Se debe suministrar una IP como argumento de entrada"
	echo "Ej: ./createFakeEthInterface.sh 198.168.1.21"
else
	sudo modprobe dummy
	sudo ip link add eth10 type dummy
	sudo ip address change dev eth10 $1
	ip address
	sudo service kubelet restart
fi
