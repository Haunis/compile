#! /usr/bin/bash

# 查看所有分支最后提交时间
# 参考：https://blog.csdn.net/auspark/article/details/125169462
# 将该脚本放在 /usr/local/bin/ 目录后，就可在terminal使用该脚本了

RED='\033[31m'
GREEN='\033[32;1m' #1是加粗字体
YELLOW='\033[33m' 
BLUE='\033[34m' 
END='\033[0m'


echo -e "${BLUE}Local Branches: ${END}"
for branch in $(git branch|sed 's/*//'); do
  if [[ ${branch} != "->" ]]; then
    echo -e ${RED}${branch}${END}
    echo -e $(git show --pretty=format:"%ci %cr" "${branch}" | head -n 1)
  fi
done

echo ""
echo -e "${BLUE}Remote Branches: ${END}"
for branch in $(git branch -r|sed 's/*//'); do
  if [[ ${branch} != "->" ]]; then
    echo -e ${RED}${branch}${END}
    echo -e $(git show --pretty=format:"%ci %cr" "${branch}" | head -n 1)
  fi
done
