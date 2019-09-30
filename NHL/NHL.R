#setwd("~/Desktop/PSM/Fall 2019/Capstone/NHL")
################################################
########### H_t ################################
rm(list = ls())
library(xtable)
X=read.csv("./hvals.csv")

## All Team data a_t computation
ALLTEAMS=X[,c(2,3,5,6,7,9)]
amod <- lm(log(a)~WINT+log(POP)+log(INC), data=ALLTEAMS)
summary(amod)
bmod <- lm(log(b)~WINT+log(POP)+log(INC), data=ALLTEAMS)
summary(bmod)

## Only WINT teams
# WINTTEAMS<-ALLTEAMS[which(ALLTEAMS$WINT==1),]
# amodWINT <- lm(log(a)~WINT+log(POP)+log(INC), data=WINTTEAMS)
# summary(amodWINT)
# bmodWINT <- lm(log(b)~WINT+log(POP)+log(INC), data=WINTTEAMS)
# summary(bmodWINT)

#Milwaukee Data
MIL=data.frame("POP"=1.572245,"INC"=73805,"WINT"=1)
(a_MIL=exp(predict(amod,MIL)))
(b_MIL=exp(predict(bmod,MIL)))
(H_MIL=(1/4)*(a_MIL^2)/(b_MIL^2))

(h_mil = H_MIL/mean(X$H_t))

#####################################################
################# S_t ###############################
X=read.csv("./success.csv")
SDat <- data.frame(X$Team,X$Revenue,X$Playoff.Appearances.Total,X$Playoff.Wins.Total,X$Stanley.Cup.Total)
S_t <- ((30/16)*SDat$X.Playoff.Appearances.Total+(30/8)*SDat$X.Playoff.Wins.Total+30*SDat$X.Stanley.Cup.Total)/sum(SDat$X.Stanley.Cup.Total)
s_t <- S_t/mean(S_t)
SDat$S_t=S_t
SDat$s_t=s_t
RevenueTable = data.frame("Team"=SDat$X.Team, "Revenue"=SDat$X.Revenue, "Playoff Appearances"=SDat$X.Playoff.Appearances.Total, "Playoff Wins"=SDat$X.Playoff.Wins.Total, "Stanley Cup Wins"=SDat$X.Stanley.Cup.Total)
print(xtable(RevenueTable, type="latex"), file="RevenueTable.tex")
STable = data.frame("Team"=SDat$X.Team, "St"=SDat$S_t, "st"=SDat$s_t)
print(xtable(STable, type="latex"), file="STable.tex")

####################################################
################### Beta_t #########################
Beta_05=0.05*SDat$s_t*ALLTEAMS$h_t
Beta_25=0.25*SDat$s_t*ALLTEAMS$h_t
Beta_75=0.75*SDat$s_t*ALLTEAMS$h_t
##############3#####################################
##################### R_0 ##########################
R_005 = Beta_05*9
R_025 = Beta_25*9
R_075 = Beta_75*9



Reprod = data.frame("Team"=X$Team, "R_0 0.05"=R_005, "R_0 0.25"=R_025, "R_0 0.75"=R_075)
