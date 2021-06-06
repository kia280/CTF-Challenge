FROM ubuntu:18.04

MAINTAINER K1a <kia@csie.io>

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y xinetd

RUN adduser --disabled-password --gecos ""  top_of_the_stack

COPY ./top_of_the_stack /home/top_of_the_stack
COPY ./xinetd /etc/xinetd.d/top_of_the_stack

RUN chown -R root:root /home/top_of_the_stack
RUN chmod -R 755 /tmp
RUN chmod -R 755 /var/tmp
RUN chmod -R 774 /dev
RUN chmod -R 774 /run

CMD ["/usr/sbin/xinetd","-dontfork"]