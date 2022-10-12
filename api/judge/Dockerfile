FROM python
WORKDIR /
USER root
RUN cd /etc/apt/ && echo "deb http://mirrors.aliyun.com/debian/ bullseye main non-free contrib \
deb-src http://mirrors.aliyun.com/debian/ bullseye main non-free contrib \
deb http://mirrors.aliyun.com/debian-security/ bullseye-security main \
deb-src http://mirrors.aliyun.com/debian-security/ bullseye-security main \
deb http://mirrors.aliyun.com/debian/ bullseye-updates main non-free contrib \
deb-src http://mirrors.aliyun.com/debian/ bullseye-updates main non-free contrib \
deb http://mirrors.aliyun.com/debian/ bullseye-backports main non-free contrib \
deb-src http://mirrors.aliyun.com/debian/ bullseye-backports main non-free contrib ">sources.list
RUN apt-get update --fix-missing
RUN apt-get install zip
RUN pip install -i https://pypi.tuna.tsinghua.edu.cn/simple psutil
RUN pip install -i https://pypi.tuna.tsinghua.edu.cn/simple --default-timeout=100 numpy
COPY data /data/
COPY game /game/
RUN cd game && ./build.sh
COPY compile /compile/
COPY 'judgeWorker.py' /
ENTRYPOINT ["python3", "judgeWorker.py"]
