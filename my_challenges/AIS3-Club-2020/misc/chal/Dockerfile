FROM ubuntu:18.04

MAINTAINER K1a <kia@csie.io>

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y python3 openssh-server vim build-essential

RUN mkdir /var/run/sshd

RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin no/' /etc/ssh/sshd_config && \
	sed -i 's/#PasswordAuthentication yes/PasswordAuthentication no/' /etc/ssh/sshd_config

RUN sed -i 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' /etc/pam.d/sshd

RUN adduser --no-create-home --disabled-password --gecos "" flaguser
RUN adduser --disabled-password --gecos "" hacker

COPY --chown=flaguser:flaguser ./flag /home/hacker
COPY --chown=flaguser:flaguser ./very-secure-script /home/hacker
COPY --chown=flaguser:flaguser ./run-very-secure-script.c /home/hacker
COPY --chown=hacker:hacker ./authorized_keys /home/hacker/.ssh/authorized_keys
COPY ./os.py /tmp
COPY ./os.py /var/tmp
COPY ./run.sh /

RUN gcc -o /home/hacker/run-very-secure-script /home/hacker/run-very-secure-script.c
RUN chown flaguser:flaguser /home/hacker/run-very-secure-script

RUN chmod 773 /tmp
RUN chmod 744 /tmp/os.py
RUN chmod 744 /var/tmp/os.py
RUN chmod 400 /run.sh
RUN chmod -R u-w,u+rX,go-w /home/hacker
RUN chmod -R go-rx /home/hacker/.ssh

RUN chmod 400 /home/hacker/flag
RUN chmod u+x,go+r /home/hacker/very-secure-script
RUN chmod u+sx,go+rx /home/hacker/run-very-secure-script
RUN chmod go+r /home/hacker/run-very-secure-script.c

EXPOSE 22

CMD ["/bin/bash", "/run.sh"]