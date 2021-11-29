kubectl delete deployment kubernetes-filemanager
sudo docker image rm manuelcerezo/serverfilemanager:1.0
sudo docker build .
echo "Introduzca id image"
read varname
sudo docker tag $varname manuelcerezo/serverfilemanager:1.0
kubectl apply -f fileManager_deployment.yaml
