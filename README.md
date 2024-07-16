# 仓库结构说明（必读！！！辛苦！！！）

**虚拟股票交易系统源码请见develop5分支！！！**

**服务器源码请见Server分支**

**股票价格走势预测所用LSTM模型源码请见Model_LSTM分支**

**实训所需文档请见Files分支！！！**

---

# 虚拟股票交易系统 AKA 股神养成计划

## 项目起源

本项目为WHU软件工程2023届24年暑期实训命题项目之一，题目描述具体如下：

**详细需求**：

· 创建一个模拟股票交易的平台，允许用户使用虚拟货币进行股票交易。
· 平台应提供实时股票数据更新、交易、资产管理等功能。

**功能点**：
1. 用户账户创建和管理功能。
2. 虚拟货币充值和提现功能。
3. 股票买入和卖出功能。
4. 实时股票行情显示功能。
5. 用户投资组合管理功能。
6. 交易历史记录和报表功能。
7. 股票市场新闻和分析功能。
8. 用户风险评估和提示功能。
9. 社交功能，如论坛和交流区。
10. 模拟交易比赛和排行榜功能。

## 团队介绍——不想起名字队

- **团队名称**：不想起名字队

- **名称寓意**：队员个性随和，相处融洽

- **团队logo**：


- **Logo寓意**：像牛马一样的我们。寓意我们勤勤恳恳，认真工作，绝不抱怨（vks：logo为ai生成，同时寓意着我们积极拥抱新技术，投身专业领域发展浪潮）

- **团队模式**：Scrum团队

- **成员组成和说明**：
  

| 姓名  | 角色     | 个人主页 | 特点说明                              |
| --- | ------ | ---- | --------------------------------- |
| 王子安 | Master |      | 社牛，非常健谈，善于与组员沟通，能够将大型目标逐步细化到具体人员。 |
| 林帆  | 技术主管   |      | 间歇性强度爆发，交际较弱，动手较强。                |
| 冯官晟 | 软件工程师  |      | 平时摆，间歇超级摆，交际较弱，动手超级弱。             |
| 李卓优 | PO     |      | 幽默，交际能力强，说的开                      |
| 郭静怡 | 测试工程师  |      | 学习能力强，不畏难。技术较弱。                   |

## 项目介绍
### 技术部分
#### 1. 架构设计
- **客户端-服务器（CS）架构**：服务器负责处理所有业务逻辑和数据存储，客户端提供用户界面和操作入口，通过TCP/IP协议进行通信，确保数据传输的稳定性和安全性。
#### 2. 前端应用
- **Qt**：用于开发跨平台的用户界面，提供丰富的UI组件和工具，支持多种平台。
- **QCustomPlot**：用于绘制实时股票K线图等图表，提供高性能的图表绘制功能。
#### 3. 后端技术
- **TCP/IP协议**：用于客户端和服务器之间的数据通信，确保数据传输的可靠性和高效性。
- **Alpha Vantage API**：用于获取近期的股票市场数据和历史数据，为平台提供精准的市场信息。
#### 4. 数据存储
- **MySQL**：关系型数据库，用于存储用户信息、交易记录、股票数据等。
- **阿里云**：提供云存储和计算服务，确保数据存储的安全性和高可用性。
#### 5. 数据分析与模型训练
- **Python爬虫**：用于抓取股票数据用于提供实时市场信息以及数据分析。
- **Pandas**：用于数据处理和分析，支持高效的数据操作和分析功能。
- **LSTM（长短期记忆网络Long Short-Term Memory）模型**：用于股票价格预测，提供更准确的市场预测，帮助用户优化投资策略。
#### 6. DevOps工具
- **Git**：版本控制系统，用于管理代码版本，支持团队协作开发。
- **Docker**：容器化技术，用于部署和管理应用，确保应用在不同环境中的一致性。
- **Jenkins**：持续集成工具，用于自动化构建、测试和部署，提升开发效率和代码质量。
- **QMake**：用于项目构建和管理，支持跨平台的项目编译和构建。
### 功能部分
- **用户账户管理**：注册、登录、修改个人信息。
- **虚拟货币交易**：存入和提取虚拟货币。
- **股票交易**：模拟股票的买入和卖出操作。
- **实时股票数据**：显示实时股票市场数据。
- **投资组合管理**：查看和管理个人投资组合。
- **交易历史与报告**：记录并展示交易历史和相关报告。
- **市场新闻与分析**：提供最新的市场新闻和专业分析。
- **用户风险评估与提醒**：对用户的投资进行风险评估并提供提醒。
- **社交功能**：用户间的论坛讨论和即时聊天。
- **模拟交易竞赛**：参与模拟交易竞赛，并在排行榜上竞争
### 特色部分
我们的虚拟股票交易平台具有以下特色：
1. **真实市场模拟**：利用**Alpha Vantage API**提供与真实市场接轨的实时数据和新闻分析。
2. **安全可靠**：采用**哈希加密**技术，为用户的数据安全提供保障
3. **多线程处理**：服务器采用QThread进行**多线程处理**，提高系统**并发处理**能力和响应速度。
4. **用户友好界面**：Qt开发的图形界面，操作简便，界面美观。
5. **图标丰富**：采用**QCustomPlot**、**QtChart**等实现了数据可视化。
6. **丰富的功能模块**：从账户管理到市场分析，功能全面，满足用户多方面需求。
7. **社交互动**：用户可以在平台上进行讨论和交流，分享交易经验。
8. **竞赛机制**：通过模拟交易竞赛，激发用户的交易兴趣，提高学习效果。
