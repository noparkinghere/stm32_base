README
===========================

### Author : damon
### E-mail : noparkinghere@foxmail.com


*使用神州开发板，stm32F439芯片，但由于某种原因，配备资料(尤其是案例)并不齐全，且2014年之后相关网站也暂停了访问
本工程目的，只要是深入学习研究这块芯片，通过参考其他M4内核的历程，将这块开发板的相关案例完善，同时去除原历程中
模糊，难懂冗余的案例，尽量做到代码规范，案例可取，便于进一步的学习研究。*


> www.armjishu.com(无法访问)


### 注意事项

- 使用芯片为stm32F439IG，市面基于这块M4内核的st芯片比较少，一般多为407
- 烧录工具位jlink或ulink，正常情况下为jlink
- 开发板的原理图可见根目录，该开发板可以在某宝找到。

### 案例列表

- 实验0 Template工程模板
- 实验1 跑马灯实验



### 注意说明


### 问题总结

在整理编写这些程序时也遇到一些问题，如：参考了EFM32的官方固件库，改写了stm32的一些内容，为了简化使用步骤，让程序容易开发，隐藏一些细节，而做了多层的命名定义，结果发现很多分装意义不大，仅仅在最初使用时略显方便，但后续会出现很多问题，对函数或者内容进行改写，增加新功能时，往往会查找起来极为麻烦，因此这边会逐一改进，去掉一些没必要的内容。
