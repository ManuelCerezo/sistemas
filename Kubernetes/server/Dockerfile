FROM ubuntu:20.04
RUN apt-get update
RUN apt-get install -y software-properties-common
RUN apt-get update

RUN mkdir server
COPY server_multMatrix /server/
RUN chmod +x /server/server_multMatrix

EXPOSE 65000
EXPOSE 80

CMD /server/server_multMatrix
