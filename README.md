## 链接汇总
+ [代码仓库](https://github.com/THU-ASTA-Technology/ASTA_website)

## 前端(/web)
+ 使用react + ant design [入门文档](#/blog/4)
+ ant design版本为3.26.7 [文档](https://3x.ant.design/docs/react/introduce-cn)
+ 程序入口为src中的index.js，其中包含了路由，调用各个不同的模块。
+ `yarn install` 安装依赖
+ `yarn start` 即可运行
+ `yarn build` 打包用于部署

## 后端(/api)
+ 使用django(python) [入门文档](#/blog/3)
+ 需要在api目录下加入asta.ini，主要用于配置邮箱信息
+ 安装完依赖后，`python3 manage.py runserver` 即可在本地运行后端
+ 程序入口为urls.py，包含路由
+ 评测模块
  + 启动评测模块需要先启动redis同时使用docker构建镜像，构建方式为在/api/judge目录下：
    ```
    docker build -t judge_box .
    ```
  + 再启动celery进行评测
    ```
    python3 manage.py celery worker -c 1
    ```

## Todo List
+ 新生C对战平台

## 依赖列表
+ 后端

  | 依赖项               | 参考版本 |
| -------------------- | -------- |
| python               | 3.7.4    |
| Django               | 3.0.2    |
| django-cors-headers  | 3.5.0    |
| django-crispy-forms  | 1.9.2    |
| django-formtools     | 2.2      |
| django-import-export | 2.3.0    |
| django-mdeditor      | 0.1.18   |
| django-reversion     | 3.0.8    |
| django-six           | 1.0.4    |
| django-stdimage      | 5.1.1    |
+ 前端依赖列表已在/web/package.json中
+ 参考版本为开发者所用版本



评测模块：

![guide](D:\environment\codes\projects\ASTA_website\guide.png)