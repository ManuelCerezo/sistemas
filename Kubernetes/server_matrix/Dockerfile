FROM ubuntu:20.04
RUN apt-get update
RUN apt-get install -y software-properties-common
RUN apt-get update

RUN mkdir server
COPY server_multMatrix /server/
COPY failsave.sh /server/
RUN chmod +x /server/server_multMatrix
RUN chmod +x /server/failsave.sh

EXPOSE 41500
EXPOSE 80

CMD /server/failsave.sh
