# data_visualization.py

import pandas as pd
import matplotlib.pyplot as plt


def showData(company_name,column_name, filePath, train_end_date, test_start_date,test_end_date):
    # 读取数据
    df = pd.read_csv(filePath, index_col='timestamp', parse_dates=["timestamp"])
    df = df.sort_index()

    # 绘制训练集数据
    df[column_name]["2010-01-30":train_end_date].plot(figsize=(16, 4), legend=True)

    # 绘制测试集数据
    df[column_name][train_end_date:test_end_date].plot(figsize=(16, 4), legend=True)

    # 绘制真实集数据
    df[column_name][test_end_date:].plot(figsize=(16, 4), legend=True)

    # 设置图例和标题
    plt.legend(['Training set (Before {})'.format(train_end_date),
                'Test set ({} and beyond)'.format(test_start_date)])
    plt.title(company_name+' Stock Price')
    plt.xlabel('Date')
    plt.ylabel('Price')
    plt.show()
