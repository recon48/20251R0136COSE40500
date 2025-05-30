FROM ubuntu:22.04

ENV user cose-451

RUN apt-get update
RUN apt-get -y install gcc gdb gcc-multilib git vim python3-pip gdbserver netcat
RUN apt-get -y install autoconf automake libtool hexedit
RUN python3 -m pip install --upgrade pip
RUN python3 -m pip install --upgrade pwntools

RUN adduser $user

ADD ./Stage5_SOS/. /home/$user/Stage5_SOS/
ADD ./Stage4_Forbidden_Archive/. /home/$user/Stage4_Forbidden_Archive/
ADD ./Stage3_Leaked_Simulator/. /home/$user/Stage3_Leaked_Simulator/
ADD ./Stage2_Innocent_sheep/. /home/$user/Stage2_Innocent_sheep/
ADD ./Stage1_Greedy/. /home/$user/Stage1_Greedy/
ADD ./Stage0_Debug_Me/. /home/$user/Stage0_Debug_Me/
ADD ./Class/. /home/$user/Class/

WORKDIR /home/$user/

RUN chmod 770 /home/$user/
RUN chmod 770 /home/$user/*/
RUN chmod 770 /home/$user/*/*.o
RUN chmod 770 /home/$user/*/*.py
RUN chmod 770 /home/$user/Stage1_Greedy/*.c
RUN chmod 770 /home/$user/Stage2_Innocent_sheep/*.c
RUN chmod 770 /home/$user/Stage3_Leaked_Simulator/*.c
RUN chmod 770 /home/$user/Stage4_Forbidden_Archive/*.c
RUN chmod 660 /home/$user/*/*.c

RUN chmod +x /home/$user/Stage0_Debug_Me/*
RUN chmod +x /home/$user/Stage1_Greedy/*
RUN chmod +x /home/$user/Stage2_Innocent_sheep/*
RUN chmod +x /home/$user/Stage3_Leaked_Simulator/*
RUN chmod +x /home/$user/Stage4_Forbidden_Archive/*
RUN chmod +x /home/$user/Stage5_SOS/*

RUN chown -R $user:$user /home/$user/*

USER $user

RUN git clone https://github.com/longld/peda.git /tmp/peda
RUN echo "source /tmp/peda/peda.py" >> ~/.gdbinit
RUN echo "DONE! debug your program with gdb and enjoy"

RUN git clone https://github.com/ksyang/file.git /home/$user/Stage5_SOS/file_oss
WORKDIR /home/$user/Stage5_SOS/file_oss
RUN autoreconf -fi
RUN mkdir build
WORKDIR /home/$user/Stage5_SOS/file_oss/build
RUN CFLAGS="-g -O0 -fno-stack-protector -no-pie" ../configure --disable-shared
RUN make

WORKDIR /home/$user
