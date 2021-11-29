FROM ubuntu:20.04
RUN apt-get update
RUN apt-get install -y software-properties-common
RUN apt-get update
RUN apt-get install -y gdb
RUN mkdir server
RUN mkdir directorio
COPY serverFileManager /server/
COPY failsave.sh /
RUN chmod +x /failsave.sh
EXPOSE 42500
EXPOSE 80
EXPOSE 443
CMD /failsave.sh
