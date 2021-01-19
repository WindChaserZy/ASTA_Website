FROM python
COPY /data /data
COPY /compile /compile
COPY 'judgeWorker.py' /
WORKDIR /
USER root
ENTRYPOINT ["python3", "judgeWorker.py"]