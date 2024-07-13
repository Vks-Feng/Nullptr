import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dropout, Dense

from data_visualization import showData
# 数据显示函数放在了data_visualization中

train_start_date="2010-01-30"
train_end_date=test_start_date="2020-12-30"
test_end_date="2022-12-30"
step=2
filePath="./Data/JBLU_monthly_data.csv"
column_name="adjusted close"
company_name="JetBlue"

# Getting the Data
df = pd.read_csv(filePath,index_col='timestamp', parse_dates=["timestamp"])
# index_col:设置timestamp为索引
# parse_dates:指定哪些列应该被解析为日期时间格式

# 确保 DataFrame 按时间顺序排序
df = df.sort_index()

# print(df.head())
# 将头几行进行打印,检测是否导入正确的数据库

# Data Visualization 数据可视化展示
showData(company_name,column_name,filePath,train_end_date,test_start_date,test_end_date)

# # Creating the Training Data
# # here we are seperating the data

# 第一种方式：只是将adjusted close这一列的数据放入到训练和测试集中
train_set = df[column_name][train_start_date:train_end_date].values
test_set = df[column_name][test_start_date:test_end_date].values

# 第二种方式：将所有列项的数据放入到训练和测试集中
# train_set = df[:train_end_date].values
# test_set = df[test_start_date:].values

# 对训练集进行重新塑形
train_set = train_set.reshape(-1,1)
test_set = test_set.reshape(-1,1)

# 数据预处理
sc = MinMaxScaler(feature_range=(0, 1))
# 使用 MinMaxScaler 将训练集数据(train_set)归一化到 [0, 1] 范围。
training_set_scaled = sc.fit_transform(train_set)

X_train = []
y_train = []

# 遍历数据集，从第 step 个样本开始
for i in range(step, len(training_set_scaled)):
    # 生成特征集，每个样本包含 step 步长（时间窗口）的数据作为特征
    # training_set_scaled[i - step:i, 0] 表示从 i-step 到 i-1 的数据，第 0 列（假设只有一列）
    X_train.append(training_set_scaled[i - step:i, 0])

    # 生成标签集，每个样本对应的下一个数据点作为标签
    # training_set_scaled[i, 0] 表示第 i 行数据的第 0 列数据（假设只有一列）
    y_train.append(training_set_scaled[i, 0])

X_train, y_train = np.array(X_train), np.array(y_train)
X_train = np.reshape(X_train, (X_train.shape[0], X_train.shape[1], 1))
# 使用 np.reshape 将 X_train 重塑为三维数组，其形状为(样本数量, 时间步数, 特征数量)。这是因为
# LSTM 模型需要输入是三维数组，其中第一个维度表示样本数量，第二个维度表示时间步，
# 第三个维度表示特征数量（这里是1维）。

# 构建LSTM模型
regressor = Sequential()
# First LSTM layer with Dropout regularisation
regressor.add(LSTM(units=100, return_sequences=True, input_shape=(X_train.shape[1],1)))
regressor.add(Dropout(0.3))

regressor.add(LSTM(units=80, return_sequences=True))
regressor.add(Dropout(0.1))

regressor.add(LSTM(units=50, return_sequences=True))
regressor.add(Dropout(0.2))

regressor.add(LSTM(units=30))
regressor.add(Dropout(0.3))

regressor.add(Dense(units=1))

regressor.compile(optimizer='adam',loss='mean_squared_error')

# 训练LSTM模型
regressor.fit(X_train, y_train, epochs=50, batch_size=32)

real_set= df[column_name][test_end_date:].values
real_set = real_set.reshape(-1,1)

# 数据预处理
dataset_total = pd.concat((df[column_name][:train_end_date],
                           df[column_name][test_start_date:]),axis=0)
inputs = dataset_total[len(dataset_total) - len(real_set) - step:].values
inputs = inputs.reshape(-1,1)
# -1 表示该维数的大小不限制（不唯一），结果就是形成一个列状的输入
inputs = sc.transform(inputs)

# 生成测试数据
X_test = []
times=1;
for i in range(step,len(inputs)):
  X_test.append(inputs[i-step:i,0])
  print(times)
  times+=1
X_test = np.array(X_test)
X_test = np.reshape(X_test, (X_test.shape[0],X_test.shape[1],1))

predicted_stock_price = regressor.predict(X_test)
predicted_stock_price = sc.inverse_transform(predicted_stock_price)

print(predicted_stock_price)
# 输出预测的数据

# 预测可视化
def plot_prediction(test,prediction):
    plt.plot(test,color='red',label="Real "+company_name+" Stock Price")
    plt.plot(prediction, color="blue",label="predicted "+company_name+" Stock price")
    plt.title(company_name+" Stock Price Prediction--step:"+str(step))
    plt.xlabel("Year")
    plt.ylabel(company_name+" Stock Price")
    plt.legend()
    plt.show()
# now we'll use this function to visualize our test and predicted data

plot_prediction(real_set,predicted_stock_price)

# 打开文件以追加模式写入
# with open('predict.txt', 'a') as file:
#     file.write(company_name + '\n')
#     file.write(predicted_stock_price+'\n')
