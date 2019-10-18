#setwd("~/Desktop/PSM/Fall 2019/Capstone/Mayo/Distributions")
rm(list = ls())
library(fitdistrplus)
library(logspline)
### Read Me in
X <- read.csv("Mayo_order_processing_data.csv",header = TRUE)

### Order Entry
orderEntry <- X$Order.Entry[!is.na(X$Order.Entry)]
hist(orderEntry) ## Looks Normal?
orderEntry.norm <- fitdist(orderEntry, "norm")
plot(orderEntry.norm)
orderEntry.norm$aic
orderEntry.weib <- fitdist(orderEntry, "weibull")
plot(orderEntry.weib)
orderEntry.weib$aic
orderEntry.exp <- fitdist(orderEntry, "exp")
plot(orderEntry.exp)
orderEntry.exp$aic
orderEntry.gam <- fitdist(orderEntry, "gamma")
plot(orderEntry.gam)
orderEntry.gam$aic








orderEntryVerification <- X$Order.Entry.Verification[!is.na(X$Order.Entry.Verification)]
hist(orderEntryVerification) ## Looks Normal?
orderEntryVerification.norm <- fitdist(orderEntryVerification, "norm")
plot(orderEntryVerification.norm)
orderEntryVerification.norm$aic
orderEntryVerification.weib <- fitdist(orderEntryVerification, "weibull")
plot(orderEntryVerification.weib)
orderEntryVerification.weib$aic
orderEntryVerification.exp <- fitdist(orderEntryVerification, "dpois")
plot(orderEntryVerification.exp)
orderEntryVerification.exp$aic
orderEntryVerification.gam <- fitdist(orderEntryVerification, "gamma")
plot(orderEntryVerification.gam)
orderEntryVerification.gam$aic





oralDrugPrep <- X$Oral.drug.prep[!is.na(X$Oral.drug.prep)]
ivDrugPrep <- X$IV.drugprep[!is.na(X$IV.drugprep)]
orderPrepVerification <- X$Order.prep.verification[!is.na(X$Order.prep.verification)]
dispensing <- X$Dispensing[!is.na(X$Dispensing)]
oralIncoming <- X$Oral.Incoming[!is.na(X$Oral.Incoming)]
ivIncoming <- X$IV.Incoming[!is.na(X$IV.Incoming)]
hist(ivIncoming)
