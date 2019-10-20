#setwd("~/Desktop/PSM/Fall 2019/Capstone/Mayo/Distributions")
rm(list = ls())
library(fitdistrplus)
library(logspline)
### Read Me in
X <- read.csv("Mayo_order_processing_data.csv",header = TRUE)

### Order Entry
orderEntry <- X$Order.Entry[!is.na(X$Order.Entry)]

#Histogram
hist(orderEntry) ## Looks Normal?
png("OrderEntryHist.png")
hist(orderEntry)
dev.off()

#Cullen Frey
descdist(orderEntry, discrete = FALSE) #Beta/Normal/Gamma/Lognormal/Weibull
png("OrderEntryCullen")
descdist(orderEntry, discrete = FALSE)
dev.off()

#Tests
###orderEntry.beta <- fitdist(orderEntry, "beta")
###plot(orderEntry.beta)
###orderEntry.beta$aic
##Normal AIC 219.8769
orderEntry.norm <- fitdist(orderEntry, "norm")
plot(orderEntry.norm)
gofstat(orderEntry.norm)
##Gamma AIC 221.3501
orderEntry.gamma <- fitdist(orderEntry, "gamma")
plot(orderEntry.gamma)
gofstat(orderEntry.gamma)
##LogNormal AIC 223.2712
orderEntry.log <- fitdist(orderEntry, "lnorm")
plot(orderEntry.log)
gofstat(orderEntry.log)
##Weibull 220.5979
orderEntry.w <- fitdist(orderEntry, "weibull")
plot(orderEntry.w)
gofstat(orderEntry.w)
##Beta
orderEntry.b <- fitdist(orderEntry/15, "beta")
plot(orderEntry.b)
gofstat(orderEntry.b)



### Entry Verification
orderEntryVerification <- X$Order.Entry.Verification[!is.na(X$Order.Entry.Verification)]

#Histogram
hist(orderEntryVerification)
png("EntryVerHist.png")
hist(orderEntryVerification)
dev.off()

#Cullen Frey
descdist(orderEntryVerification, discrete = FALSE) #
png("OrderEntryVerCullen")
descdist(orderEntryVerification, discrete = FALSE)
dev.off()

##Uniform
orderEntryVer.uni <- fitdist(orderEntryVerification, "unif", method="mle")
plot(orderEntryVer.uni)
gofstat(orderEntryVer.uni)
##Normal AIC 79.06169
orderEntryVer.norm <- fitdist(orderEntryVerification, "norm")
plot(orderEntryVer.norm)
gofstat(orderEntryVer.norm)
##Gamma AIC 78.97119
orderEntryVer.gamma <- fitdist(orderEntryVerification, "gamma")
plot(orderEntryVer.gamma)
gofstat(orderEntryVer.gamma)
##LogNormal AIC 79.87167
orderEntryVer.log <- fitdist(orderEntryVerification, "lnorm")
plot(orderEntryVer.log)
gofstat(orderEntryVer.log)



###Oral Prep
oralDrugPrep <- X$Oral.drug.prep[!is.na(X$Oral.drug.prep)]

#Histogram
hist(oralDrugPrep)
png("OralPrepHist.png")
hist(oralDrugPrep)
dev.off()

#Cullen Frey
descdist(oralDrugPrep, discrete = FALSE) #
png("OralPrepCullen")
descdist(oralDrugPrep, discrete = FALSE)
dev.off()

##Normal AIC 169.1392
oralDrugPrep.norm <- fitdist(oralDrugPrep, "norm")
plot(oralDrugPrep.norm)
gofstat(oralDrugPrep.norm)
##Gamma AIC 168.7099
oralDrugPrep.gamma <- fitdist(oralDrugPrep, "gamma")
plot(oralDrugPrep.gamma)
gofstat(oralDrugPrep.gamma)
##LogNormal AIC 168.5827
oralDrugPrep.log <- fitdist(oralDrugPrep, "lnorm")
plot(oralDrugPrep.log)
gofstat(oralDrugPrep.log)
##Weibull 176.7090
oralDrugPrep.w <- fitdist(oralDrugPrep, "weibull")
plot(oralDrugPrep.w)
gofstat(oralDrugPrep.w)

oralDrugPrep.b <- fitdist(oralDrugPrep/25, "beta")
plot(oralDrugPrep.b)
gofstat(oralDrugPrep.b)

oralDrugPrep.b <- fitdist(((oralDrugPrep-min(oralDrugPrep))/(max(oralDrugPrep)-min(oralDrugPrep))), "beta")
plot(oralDrugPrep.b)
gofstat(oralDrugPrep.b)



ivDrugPrep <- X$IV.drugprep[!is.na(X$IV.drugprep)]
orderPrepVerification <- X$Order.prep.verification[!is.na(X$Order.prep.verification)]
dispensing <- X$Dispensing[!is.na(X$Dispensing)]
oralIncoming <- X$Oral.Incoming[!is.na(X$Oral.Incoming)]
ivIncoming <- X$IV.Incoming[!is.na(X$IV.Incoming)]
hist(ivIncoming)
