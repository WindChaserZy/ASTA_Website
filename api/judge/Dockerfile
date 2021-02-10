FROM python
RUN pip install -i https://pypi.tuna.tsinghua.edu.cn/simple psutil
RUN pip install -i https://pypi.tuna.tsinghua.edu.cn/simple --default-timeout=100 numpy
COPY /data /data
COPY /game /game
COPY /compile /compile
COPY 'judgeWorker.py' /
WORKDIR /
USER root
ENTRYPOINT ["python3", "judgeWorker.py"]
