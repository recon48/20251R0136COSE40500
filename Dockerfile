FROM ubuntu:22.04

ENV user bob
ENV chall_port 31331

RUN apt-get update
RUN apt-get -y install socat gcc gcc-multilib

RUN adduser $user

WORKDIR /home/$user

ADD Stage1_Mallory.o /home/$user/Stage_Debug_Me
ADD flag.txt /home/$user/flag.txt

RUN chown -R root:$user /home/$user
RUN chown root:$user /home/$user/Stage_Debug_Me
RUN chown root:$user /home/$user/flag.txt

RUN chmod 111 /home/$user/Stage_Debug_Me
RUN chmod 444 /home/$user/flag.txt

USER $user
EXPOSE $chall_port
CMD socat -T 30 TCP-LISTEN:$chall_port,reuseaddr,fork EXEC:/home/$user/Stage_Debug_Me