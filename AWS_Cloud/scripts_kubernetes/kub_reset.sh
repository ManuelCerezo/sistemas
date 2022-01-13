sudo kubeadm reset
sudo apt-get purge -y kubectl kubeadm kubernetes-cni
sudo rm -r /etc/kubernetes/
sudo rm -r /var/lib/etcd/
sudo rm -r /opt/cni
rm -r ~/.kube

sudo apt-get purge docker.io
sudo rm -r /etc/docker

