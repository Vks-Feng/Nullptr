# 使用基础的 Ubuntu 20.04 镜像
FROM ubuntu:noble

# 设置 DEBIAN_FRONTEND 环境变量
ENV DEBIAN_FRONTEND=noninteractive

# 设置时区环境变量并配置 tzdata
ENV TZ=Asia/Shanghai

RUN ln -fs /usr/share/zoneinfo/$TZ /etc/localtime && \
    echo $TZ > /etc/timezone && \
    apt-get update && \
    apt-get install -y tzdata

# 设置工作目录
WORKDIR /app

# 更新安装包列表并安装必要的依赖
RUN apt-get update \
    && apt-get install -y  build-essential \  			 
                          qt6-base-dev \
                          qt6-base-dev-tools \
                          qt6-charts-dev \
                          libmysqlclient-dev \   
    && rm -rf /var/lib/apt/lists/*

# 复制你的项目文件到工作目录
COPY . /app

# 使用 qmake6 生成 Makefile 并编译项目
RUN qmake6 VirtualStock_dir/VirtualStock.pro \
    && make

# 定义容器启动时执行的命令
#CMD ["./VirtualStock"]
