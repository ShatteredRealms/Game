##########
# LEGACY #
##########
FROM debian:latest

RUN apt-get update \
    && apt-get upgrade -y \
    && apt-get install -y xdg-user-dirs xdg-utils procps

RUN adduser server
ARG version=latest
COPY ./Package/${version}/Shipping/LinuxServer /home/server/server
RUN chown -R server:server /home/server
RUN chmod o+x /home/server/server

USER server

EXPOSE 7777/udp

ENTRYPOINT ["/home/server/server/SROServer.sh"]
