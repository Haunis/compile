#! /bin/bash

RED='\033[31m'
GREEN='\033[32;1m' #1是加粗字体
YELLOW='\033[33m' 
BLUE='\033[34m' 
END='\033[0m'

player1=xiaoming #define a player1
player2=ken
echo "Game start! $player1 vs $player2" #echo is used to printf in terminal


echo -e "${RED}this is red ${END}" #要使用 -e
echo -e "${GREEN}this is green ${END}"
echo -e "${BLUE}this is blue ${END}"
