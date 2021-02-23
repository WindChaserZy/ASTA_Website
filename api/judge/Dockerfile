FROM python
WORKDIR /
USER root
RUN pip install -i https://pypi.tuna.tsinghua.edu.cn/simple psutil
RUN pip install -i https://pypi.tuna.tsinghua.edu.cn/simple --default-timeout=100 numpy
COPY /data /data
COPY /game /game
RUN cd game && ./build.sh
COPY /compile /compile
COPY 'judgeWorker.py' /
ENTRYPOINT ["python3", "judgeWorker.py"]
