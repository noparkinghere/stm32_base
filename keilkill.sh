#! /bin/bash
# 清除keil中每次编译后的文件。
find . -name "*.bak  *.ddk *.edk  *.lst  *.lnp  *.mpf  *.mpj  *.obj  *.omf  *.plg  *.rpt  *.tmp *.__i  *.crf  *.o  *.d  *.axf  *.tra  *.dep JLinkLog.txt  *.iex  *.htm  *.sct  *.map"
#| xargs rm -f
