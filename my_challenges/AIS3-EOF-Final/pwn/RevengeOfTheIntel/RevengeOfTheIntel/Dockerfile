FROM ubuntu:focal
MAINTAINER K1a

RUN apt-get update
RUN apt-get install xinetd hashcash -qy
RUN useradd -m RevengeOfTheIntel

CMD ["/usr/sbin/xinetd","-dontfork"]
