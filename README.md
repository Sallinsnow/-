# 最最简单的嵌入式示波器
仅作为记录使用，因为是期末作业，所以功能实现非常简陋，只完成了以下功能：
- [x] 采集数据
- [x] 存储数据
- [x] ui设计
- [x] 波形显示
- [x] 时间档位转换
- [x] 生成示例方波


值得一提的是，波形转换功能由于我的代码设计的不完美，经常会在转换的时候卡死。推测是因为数据采集的速度和内部时钟产生了冲突，由于我设计的函数在中断回调函数部分代码过多，导致回调函数花费的时间过长，一方面，时钟已经触发开始了采集数据，而代码仍然在执行回调函数，另一方面，可能因为数据采集的数据过多导致数组溢出。总之，转换部分做的很垃圾，有机会再改吧。另外，其实示波器的原理还是有很多没有弄明白的地方，以后再说。
