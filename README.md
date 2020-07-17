# CPU Monitor

## 简介
一款仿任务管理器的能够实时显示 CPU 利用率的 `electron` 桌面应用

## 技术路线
用 C++ 编写一个获取 CPU 信息的函数，用 `node-gyp` 打包这个 C++ 模块，然后在 js 中使用这个模块。使用 `echarts` 来绘制折线图，每秒钟更新一次图表数据。

## 运行截图
![avatar](./screenshots/与任务管理器的对比.png)